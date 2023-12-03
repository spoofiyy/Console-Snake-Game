#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stack>
#include <queue>

using namespace std;

bool gameOver;
const int boardSizeX = 20;
const int boardSizeY = 20;
char board[boardSizeX][boardSizeY];
int x, y, foodX, foodY, score;
int tailX[boardSizeX * boardSizeY];
int tailY[boardSizeX * boardSizeY];
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir, tempDir;
queue<int> foodPosX;
queue<int> foodPosY;
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
        tail = nullptr;
    }

    void addHead(char body) {
        Node* newNode = new Node(body);
        head = newNode;
        tail = newNode;
    }

    void addBody(char body) {
        Node* newNode = new Node(body);
        Node* temp = head;

        while(temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = newNode;
        tail = newNode;
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
    
    Node* getTail() {
        return tail;
    }

    int countBody() {
        Node* temp = head;

        int i = 0;

        while(temp != nullptr) {
            i++;
            temp = temp->next;
        }

        return i;
    }
}; 

Snake snake;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = boardSizeX / 2;
    y = boardSizeY / 2;
    foodPosX.push(rand() % (boardSizeX-2));
    foodPosY.push(rand() % (boardSizeY-2));
    foodX = foodPosX.front();
    foodY = foodPosY.front();
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
            if(j == 0) {
                board[i][j] = '#';
                cout << board[i][j];
            }
            if(i == y && j == x) {
                if(snake.getHead() == nullptr) {
                    snake.addHead('O');
                }
                board[i][j] = snake.getHead()->snakeBody;
                cout << board[i][j];
            }else if(i == foodPosY.front() && j == foodPosX.front()) {
                cout << 'F';
            }else {
                bool print = false;
                for(int k = 0; k < snake.countBody() && snake.getHead() != snake.getTail(); k++) {
                    if(tailX[k] == j && tailY[k] == i) {
                        board[i][j] = snake.getTail()->snakeBody;
                        cout << board[i][j];
                        print = true;
                    }
                }
                if(!print && j < boardSizeY - 2) {
                    board[i][j] = ' ';
                    cout << board[i][j];
                }
            }
            if(j == boardSizeX-2) {
                cout << "#";
            }
        }
        cout << endl;
    }

    for(int i = 0; i < boardSizeX; i++){
        board[boardSizeX-1][i] = '#';
        cout << board[boardSizeX-1][i];
    }
    cout << "\nScore: " << score << endl;
}

void Input() {
    if(_kbhit()) {
        switch(_getch()) {
            case 'w':
                if(dir == DOWN && snake.getHead() != snake.getTail())
                    break;
                dir = UP;
                break;
            case 'a':
                if(dir == RIGHT && snake.getHead() != snake.getTail())
                    break;
                dir = LEFT;
                break;
            case 's':
                if(dir == UP && snake.getHead() != snake.getTail())
                    break;
                dir = DOWN;
                break;
            case 'd':
                if(dir == LEFT && snake.getHead() != snake.getTail())
                    break;
                dir = RIGHT;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void Logic() { 
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for(int i = 1; i < snake.countBody(); i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch(dir)
    {
        case UP:
            position.push(--y);
            y = position.top();
            position.pop();
            break;
        case LEFT:
            position.push(--x);
            x = position.top();
            break;
        case DOWN:
            position.push(++y);
            y = position.top();
            break; 
        case RIGHT:
            position.push(++x);
            x = position.top();
            break;
        default:
            break;
    }
    if(x > boardSizeX-3 || x < 0 || y > boardSizeY-1 || y < 0) {
        gameOver = true;
    }

    for(int i = 1; i < snake.countBody(); i++) {
        if(tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }
    
    if(x == foodX && y == foodY) {
        score += 1;
        foodPosX.pop();
        foodPosY.pop();
        
        int foodRandX = rand() % (boardSizeX-2);
        int foodRandY = rand() % (boardSizeY-2);

        while(foodRandX == x && foodRandY == y) {
            foodRandX = rand() % (boardSizeX-2);
            foodRandY = rand() % (boardSizeY-2);
        }

        foodPosX.push(foodRandX);
        foodPosY.push(foodRandY);
        foodX = foodPosX.front();
        foodY = foodPosY.front();
        snake.addBody('o');
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

