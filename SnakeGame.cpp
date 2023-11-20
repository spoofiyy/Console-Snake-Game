#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

bool gameOver;
const int boardSize = 20;
char board[boardSize][boardSize];
int x, y, foodX, foodY;

class Node{
public:
    char snakeBody;
    Node* next;

    Node(char snakeBody) {
        this->snakeBody = snakeBody;
        next = nullptr;
    }
};

class Snake{
    Node* head;
    Node* tail;
public:
    Snake() {
        head = nullptr;
    }

    void addBody(char body) {
        Node* newNode = new Node(body);

        if(head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while(temp->next != nullptr) {
                temp = temp->next;
            }

            temp->next = newNode;
            tail = newNode;
        }
    }

    void printSnake() {
        Node* temp = head;

        if(head == nullptr) {
            cout << "List Empty" << endl;
            return;
        } 

        while (temp != nullptr) {
            cout << temp->snakeBody;
            temp = temp->next;
        }
    }

    void removeTail() {
        if(head == nullptr) {
            return;
        }

        if(head->next == nullptr) {
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }

        Node* temp = head;
        while(temp->next->next != nullptr) {
            temp = temp->next;
        }

        delete temp->next;
        temp->next = nullptr;
        tail = temp;
    }
}; 

void Setup() {
    gameOver = false;
}

void Draw() {
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
        Sleep(10);
    }

    return 0;
}