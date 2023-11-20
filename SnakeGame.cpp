#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

bool gameOver;
const int boardSizeX = 20;
const int boardSizeY = 20;
char board[boardSizeX][boardSizeY];
int x, y, foodX, foodY, score;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

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
    dir = STOP;
    x = boardSizeX / 2;
    y = boardSizeY / 2;
    foodX = rand() %  boardSizeX;
    foodY = rand() %  boardSizeY;
    score = 0;
}

void Draw() {
    system("CLS");
    
    for(int i = 0; i < boardSizeX; i++){
        board[0][i] = '#';
        cout << board[0][i];
    }
    cout << endl;

    for(int i = 0; i < boardSizeX; i++) {
        for(int j = 0; j < boardSizeY; j++) {
            if(j == 0 || j == boardSizeY - 1) {
                board[i][j] = '#';
                cout << board[i][j];
            }else {
                board[i][j] = ' ';
                cout << board[i][j];
            }
        }
        cout << endl;
    }

    for(int i = 0; i < boardSizeX; i++){
        board[boardSizeX-1][i] = '#';
        cout << board[boardSizeX-1][i];
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