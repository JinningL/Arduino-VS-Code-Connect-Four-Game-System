#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

#define ROWS 6
#define COLS 6
#define EMPTY '-'
#define RED 'R'
#define YELLOW 'Y'

char board[ROWS][COLS];
char currentPlayer = RED;

void printBoard() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

bool insertPiece(int col) {
    if (col < 0 || col >= COLS) return false;
    for (int i = ROWS - 1; i >= 0; --i) {
        if (board[i][col] == EMPTY) {
            board[i][col] = currentPlayer;
            return true;
        }
    }
    return false;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == RED) ? YELLOW : RED;
}

bool checkDirection(int row, int col, int dRow, int dCol) {
    char first = board[row][col];
    if (first == EMPTY) return false;
    for (int i = 1; i < 4; ++i) {
        int r = row + dRow * i, c = col + dCol * i;
        if (r < 0 || r >= ROWS || c < 0 || c >= COLS || board[r][c] != first)
            return false;
    }
    return true;
}

bool checkWin() {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (checkDirection(row, col, 1, 0) ||
                checkDirection(row, col, 0, 1) ||
                checkDirection(row, col, 1, 1) ||
                checkDirection(row, col, 1, -1))
                return true;
        }
    }
    return false;
}

void flashWin(int fd) {
    char signal = (currentPlayer == RED) ? 'R' : 'Y';
    for (int i = 0; i < 6; ++i) {
        write(fd, &signal, 1);
        usleep(300000);
    }
    std::cout << "🏆 Winner: " << (currentPlayer == RED ? "Red" : "Yellow") << "!\n";
}

void flashDraw(int fd) {
    for (int i = 0; i < 6; ++i) {
        write(fd, "D", 1);
        usleep(300000);
    }
    std::cout << "🤝 It's a draw!\n";
}

int openSerial(const char* device) {
    int fd = open(device, O_RDWR | O_NOCTTY);
    if (fd < 0) return -1;

    struct termios tty = {};
    tcgetattr(fd, &tty);
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_cflag &= ~(PARENB | PARODD | CSTOPB | CRTSCTS);
    tty.c_cflag |= CREAD | CLOCAL;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_iflag = 0;
    tcsetattr(fd, TCSANOW, &tty);

    return fd;
}

int main() {
    for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < COLS; ++j)
            board[i][j] = EMPTY;

    int fd = openSerial("/dev/cu.usbmodem101");
    if (fd < 0) {
        std::cerr << "❌ Failed to open serial port.\n";
        return 1;
    }

    int moves = 0;
    while (true) {
        printBoard();
        std::cout << (currentPlayer == RED ? "🔴 Red" : "🟡 Yellow") << "'s turn...\n";

        char buf;
        int bytesRead = read(fd, &buf, 1);
        if (bytesRead > 0) {
            if (buf == '*') {
                std::cout << "🚪 Game exited.\n";
                break;
            }
            int col = buf - '1';
            if (col >= 0 && col < COLS) {
                if (insertPiece(col)) {
                    moves++;
                    if (checkWin()) {
                        printBoard();
                        flashWin(fd);
                        break;
                    } else if (moves == ROWS * COLS) {
                        printBoard();
                        flashDraw(fd);
                        break;
                    }
                    switchPlayer();
                } else {
                    std::cout << "⚠️ Column full!\n";
                }
            } else {
                std::cout << "❌ Invalid key: " << buf << "\n";
            }
        }
    }
    close(fd);
    return 0;
}