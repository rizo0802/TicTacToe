#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

int xPins[9] = {15, 4, 18, 21, 23, 26, 13, 14, 32}, oPins[9] = {2, 5, 19, 22, -1, 25, 12, 27, 33}, resetButtonPin = 36;  
char board[3][3],lastPlayer = ' '; 
bool IsGameOver = false;  


void StartTheGame() {

  for (int i = 0; i < 9; i++) {
    pinMode(xPins[i], OUTPUT);
    digitalWrite(xPins[i], HIGH);
    if (oPins[i] != -1) {
      pinMode(oPins[i], OUTPUT);  
      digitalWrite(oPins[i], HIGH); 
    } 
    }

  for (int i = 0; i < 3; i++) {
  for (int j = 0; j < 3; j++) {
      board[i][j] = ' ';
    }
    }
lastPlayer = ' ';
IsGameOver = false; 
}


void UserPickedLed(int PositionOnBoard, char player) {

  if (player == 'X') {
    digitalWrite(xPins[PositionOnBoard], LOW); 
    digitalWrite(oPins[PositionOnBoard], HIGH); 
  } else if (player == 'O') {
    digitalWrite(oPins[PositionOnBoard], LOW); 
    digitalWrite(xPins[PositionOnBoard], HIGH);  
  }
}


char IsThereAWinner() {  

  if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
    return board[0][0];
   }
  if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
    return board[0][2];
  }
  for (int i = 0; i < 3; i++) {
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
      return board[i][0];
    }
    if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
      return board[0][i];
    }
    }
  return ' ';
}

bool CheckIfDraw() {
int i,j;
  for (i= 0; i < 3; i++) {
    for (j= 0; j < 3; j++) {
      if (board[i][j]== ' ') {
        return false;
      }
      }
      }
  return true;
}


void ResetButtonCheck() {
  if (digitalRead(resetButtonPin)== LOW && IsGameOver){  
    SerialBT.println("Game has been reset.");
    StartTheGame();
  }
  }


void ProcessUserInput() {

  if (SerialBT.available() && !IsGameOver){  // Only handle UserInputs if the game is not over
    String UserInput=SerialBT.readStringUntil('\n');
    UserInput.trim();

  if (UserInput.length()==2){

    int PositionOnBoard=UserInput.charAt(0) - '1';
    char player=UserInput.charAt(1);

  if (PositionOnBoard >=0 && PositionOnBoard<9 && (player=='X' || player=='O')) {

        int RowOfBoard=PositionOnBoard / 3;
        int CollumOfBoard=PositionOnBoard % 3;

       
  if (player==lastPlayer) {

     SerialBT.println("It was already your turn");
      return;
        }

  if (board[RowOfBoard][CollumOfBoard] == ' ') {

    board[RowOfBoard][CollumOfBoard] = player;
    UserPickedLed(PositionOnBoard, player);
    lastPlayer = player;  

    char winner = IsThereAWinner();

    if (winner != ' ') {

    SerialBT.print("The winner has been decided and it is: ");
    SerialBT.println(winner);
    IsGameOver= true;  
      }
        else if (CheckIfDraw()) {
        SerialBT.println("Draw");
        IsGameOver= true;  
          }
          } 
        else {
        SerialBT.println("Spot is already taken");
         }
         } 
      else {
      SerialBT.println("Please only use 'PositionNumber'X/O");
         }
         }
         }
         }

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32_XandO");
  pinMode(resetButtonPin, INPUT);
  StartTheGame();

}

void loop() {

  ProcessUserInput();
  ResetButtonCheck();
}
