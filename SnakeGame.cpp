#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stack>

using namespace std;

bool gameOver;
const int boardSizeX = 20;
const int boardSizeY = 20;
char board[boardSizeX][boardSizeY];
int x, y, foodX, foodY, score;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

stack<int> position;

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

    Node* getHead() {
        return head;
    }
}; 

Snake snake;

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

    for(int i = 0; i < boardSizeY; i++) {
        for(int j = 0; j < boardSizeX; j++) {
            if(j == 0 || j == boardSizeX - 2) {
                board[i][j] = '#';
                cout << board[i][j];
            }
            if(i == y && j == x) {
                if(snake.getHead() == nullptr) {
                    snake.addBody('O');
                }
                board[i][j] = snake.getHead()->snakeBody;
                cout << board[i][j];
            }else if(i == foodY && j == foodX) {
                cout << 'F';
            }else {
                if(j < boardSizeX-2) {
                    board[i][j] = ' ';
                    cout << board[i][j];
                }
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
    if(_kbhit()) {
        switch(_getch()) {
            case 'w':
                dir = UP;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void Logic() { 
    switch (dir)
    {
        case UP:
            position.push(--y);
            y = position.top();
            position.pop();
            break;
        case LEFT:
            position.push(--x);
            x = position.top();
            position.pop();
            break;
        case DOWN:
            position.push(++y);
            y = position.top();
            position.pop();
            break; 
        case RIGHT:
            position.push(++x);
            x = position.top();
            position.pop();
            break;
        default:
            break;
    }
    if (x > boardSizeX-3 || x < 0 || y > boardSizeY-1 || y < 0) {
        gameOver = true;
    }
    
}

int main() {
    Setup(); 

    while(!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(40);
    }

    return 0;
}