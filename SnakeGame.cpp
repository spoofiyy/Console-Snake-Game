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
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN}; // State constants
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
    // Place starting head on the middle of the board
    x = boardSizeX / 2; 
    y = boardSizeY / 2; 
    // Initial food position
    foodPosX.push(rand() % (boardSizeX-2));
    foodPosY.push(rand() % (boardSizeY-2));
    foodX = foodPosX.front();
    foodY = foodPosY.front();
    score = 0;
    tailX, tailY;

}

int tempx, tempy;
void Draw() {
    system("CLS");
    
    // Top edge of the board
    for(int i = 0; i < boardSizeX; i++){
        board[0][i] = '#';
        cout << board[0][i];
    }
    cout << endl;

    // Middle board
    for(int i = 0; i < boardSizeY; i++) {
        for(int j = 0; j < boardSizeX; j++) {
            // Left edge of the board
            if(j == 0) {
                board[i][j] = '#';
                cout << board[i][j];
            }
            // Intialize head of the snake in the middle of the board
            if(i == y && j == x) {
                if(snake.getHead() == nullptr) {
                    snake.addHead('O');
                }
                board[i][j] = snake.getHead()->snakeBody;
                cout << board[i][j];
            // Display food randomly in the board
            }else if(i == foodPosY.front() && j == foodPosX.front()) {
                cout << 'F';
            }else {
                // Print body extension
                bool print = false;
                for(int k = 0; k < snake.countBody() && snake.getHead() != snake.getTail(); k++) { // Body extension
                    if(tailX[k] == j && tailY[k] == i) {
                        board[i][j] = snake.getTail()->snakeBody;
                        cout << board[i][j];
                        print = true;
                        tempx = k;
                    }
                    
                }
                if(!print && j < boardSizeY - 2) { // Print space only if not the coordinates of the body
                    board[i][j] = ' ';
                    cout << board[i][j];
                }
            }
            // Right edge of the board
            if(j == boardSizeX-2) {
                cout << "#";
            }
        }
        cout << endl;
    }

    // Bottom edge of the board
    for(int i = 0; i < boardSizeX; i++){
        board[boardSizeX-1][i] = '#';
        cout << board[boardSizeX-1][i];
    }
    // Track score
    cout << "\nScore: " << score << endl;
}

void Input() {
    // Process the pressed key
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
    // Variables to keep track of the position of the body extension
    int prevX = tailX[1]; // Store previous x-coord of the second segment of the snake body
    int prevY = tailY[1]; // Store previous y-coord of the second segment of the snake body
    int prevXX, prevYY; // For temporary storage of the previous coordinates of the current segment
    tailX[1] = x; // Initialize the second segment as the x-coord of the head
    tailY[1] = y; // Initialize the second segment as the y-coord of the head

    // Body movement implementation 
    // oooO -> ooo O -> oo oO -> o ooO -> -oooO
    for(int i = 2; i < snake.countBody(); i++) {
        prevXX = tailX[i];
        prevYY = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prevXX;
        prevY = prevYY;
    }

    // Constant movement with -1 or +1 in x and y axis
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
    // Board collision
    if(x > boardSizeX-3 || x < 0 || y > boardSizeY-1 || y < 0) {
        gameOver = true;
    }

    // Body collision
    for(int i = 1; i < snake.countBody(); i++) {
        if(tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }
    
    // Add body 'o' when snake hits 'F'
    if(x == foodX && y == foodY) {
        score += 1;
        foodPosX.pop();
        foodPosY.pop();
        
        int foodRandX, foodRandY;
        bool foodPosFlag;
        // Generate random x and y coordinates
        do {
            foodRandX = rand() % (boardSizeX-2);
            foodRandY = rand() % (boardSizeY-2);
            foodPosFlag = false;

            // Avoid spawning of food on the body of the snake
            for (int i = 0; i < snake.countBody(); i++) {
                if (tailX[i] == foodRandX && tailY[i] == foodRandY) {
                    foodPosFlag = true;
                    break;
                }
            }
        }while(foodPosFlag);
        
        foodPosX.push(foodRandX);
        foodPosY.push(foodRandY);
        // Get x y coordinates for the food
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
        Sleep(100);
    }

    return 0;
}

