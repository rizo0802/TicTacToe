# Bluetooth Tic-Tac-Toe 🎮

An interactive, physical Tic-Tac-Toe game built with an ESP32 microcontroller. The game state is displayed using physical LEDs and controlled remotely via Bluetooth Serial communication.

## Features
* **Bluetooth Remote Control:** Send moves directly from your phone or PC using a standard Bluetooth Serial terminal.
* **Physical Game Board:** Dynamically drives 17 individual LEDs across the ESP32's GPIO pins to indicate 'X' and 'O' positions.
* **Real-Time Game Logic:** Automatically validates whose turn it is, prevents overwriting taken spots, and calculates win/draw conditions.
* **Hardware Reset:** Includes a physical push-button integrated via GPIO to instantly clear the board and restart the game.

## How It Works
The ESP32 runs the game loop and waits for a Bluetooth connection. To play:
1. Connect to the device named `ESP32_XandO` using a Bluetooth terminal app.
2. Send a 2-character command to make a move: the board position (1-9) followed by the player (X or O). For example, typing `5X` claims the center square for X.
3. The program processes the string, updates the 2D array, and lights up the corresponding physical LED.
4. When a winner is decided or a draw occurs, press the physical reset button on the board to clear the LEDs and play again.

## Getting Started

### Prerequisites
* **Arduino IDE** with the ESP32 board package installed.
* A **Bluetooth Serial Terminal** app on your phone or PC.
* The physical circuit (an ESP32, LEDs, resistors, and a push-button).

### Compilation & Execution
To compile and run the project:

1. Open the `.ino` file in the Arduino IDE.
2. Select your specific ESP32 board model from the Tools menu.
3. Compile and upload the code to the microcontroller.
4. Open your Bluetooth app, connect, and start sending moves!
