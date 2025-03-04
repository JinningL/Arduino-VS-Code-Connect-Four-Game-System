
# Arduino × VS Code Connect Four Game

## 📌 Project Description
This project integrates **Arduino** and **VS Code (C++)** to create a **Connect Four game**.  
- The **Arduino** side handles player input via a **keypad** and uses **LEDs** to indicate turns and game results.
- The **VS Code** side manages the **game logic**, **win detection**, and receives column inputs from Arduino through **serial communication**.

---

## 🎮 How to Play
- **Players:** Red 🔴 and Yellow 🟡 alternate turns.
- **Keypad Input:**  
  - Press **1-6** to choose the column (left to right).
  - Press **`*`** to exit the game.
- **Winning:** Get **4 pieces in a row** (horizontally, vertically, or diagonally).
- **Draw:** If the board is full and no winner.
- **LEDs:**
  - 🔴 Red LED on: Red player's turn.
  - 🟡 Yellow LED on: Yellow player's turn.
  - Flashing LEDs: Game over (win or draw).

---

## 🛠️ Hardware Requirements
- Arduino board (such as Mega 2560)
- 4x4 Keypad
- 2 LEDs (Red & Yellow)
- Resistors (220Ω)
- Wires & Breadboard
- USB cable (for serial communication)

---

## ⚡ Wiring Diagram
| Component      | Arduino Pin |
|---------------|-------------|
| Red LED      | D41         |
| Yellow LED   | D43         |
| Keypad Rows  | D2, D3, D4, D5 |
| Keypad Columns | D6, D8, D7, D9 |

---

## 💻 Software Setup

### Arduino Side
- Upload the **Arduino code** via Arduino IDE.
- The Arduino:
  - Reads the keypad.
  - Sends column number via Serial.
  - Controls LEDs to indicate the current player and endgame status.

### VS Code Side
- Compile and run the **C++ code**.
- Reads keypad input from the serial port.
- Executes the Connect Four game logic.
- Detects wins, draws, and updates the board display.

---

## 🔗 Serial Communication
- **Baud Rate:** 9600
- **Port:** Match your Arduino device path (example: `/dev/cu.usbmodem101`).

---

## 🚀 How to Run
1. Connect Arduino and upload the code.
2. Run the VS Code program.
3. Start pressing keys (**1-6**) to play.
4. Watch the LEDs for turn indication.
5. When the game ends:
   - Winner’s LED flashes.
   - If it's a draw, both LEDs flash.
6. Press **`*`** to exit the game.

---

## 📂 Files Included
- `game.cpp` (VS Code C++ logic)
- `arduino.ino` (Arduino keypad + LED control)
- `README.md` (Project description)

---

## 📌 Project Name
**Arduino & VS Code Interactive Connect Four Game**

---

## 🙌 Author
Designed by **liujinning** with support from ChatGPT.

---

## 📅 Version
**v1.0 - March 2025**
