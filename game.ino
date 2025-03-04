#include <Keypad.h>

#define RED_LED_PIN 41
#define YELLOW_LED_PIN 43

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};  
byte colPins[COLS] = {6, 8, 7, 9};  

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char currentPlayer = 'R';
bool gameRunning = true;

void setup() {
  Serial.begin(9600);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  digitalWrite(RED_LED_PIN, HIGH);   // 红灯先亮
  digitalWrite(YELLOW_LED_PIN, LOW);
}

void loop() {
  if (gameRunning) {
    char key = keypad.getKey();
    if (key) {
      if (key == '*') {           // 按 * 退出游戏
        gameRunning = false;
        endGame();
      } else if (key >= '1' && key <= '6') {  // 只接受 1-6 作为合法输入
        switchPlayer();          // 切换回合和灯光
        Serial.write(key);       // 发送按键到 VS Code
      }
    }
  }
}

void switchPlayer() {
  if (currentPlayer == 'R') {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    currentPlayer = 'Y';
  } else {
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    currentPlayer = 'R';
  }
}

void endGame() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    delay(300);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    delay(300);
  }
}