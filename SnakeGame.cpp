#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

bool gameOver;

void Setup() {
    gameOver = false;
}

void Draw() {

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
    }

    return 0;
}