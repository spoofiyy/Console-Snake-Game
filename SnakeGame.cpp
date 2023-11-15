#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

bool gameOver;

void Setup() {
    gameOver = false;
}

void Draw() {
    int boardSize = 20;
    char board[boardSize][boardSize];

    system("CLS");

    for(int i = 0; i < boardSize; i++) {
        for(int j = 0; j < boardSize; j++) {
            if(j == 0 || j == boardSize - 1 || i == 0 || i == boardSize - 1) {
                board[i][j] = '#';
                cout << board[i][j];
            }else {
                board[i][j] = ' ';
                cout << board[i][j];
            }
        }
        cout << endl;
    }
}

void Input() {

}

void Logic() { 

}

int main() {
    Setup(); 

    while(!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(50);
    }

    return 0;
}