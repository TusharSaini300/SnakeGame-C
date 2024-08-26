#include <iostream>
#include <conio.h>  // For _getch()
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include<windows.h>

using namespace std;

bool gameover;
const int height = 20;
const int width = 20;

int x, y, fruitX, fruitY, score;
int nTail,xTail[100],yTail[100];

enum eDirection { STOP = 0, UP, DOWN, RIGHT, LEFT };
eDirection dir;

void setup() {
    gameover = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void board() {
    system("cls"); 
    for (int i = 0; i < width+1 ; i++) {
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) {
                cout << "#";
            }
            if (i == y && j == x) {
                cout << "O";  // Snake head
            } else if (i == fruitY && j == fruitX) {
                cout << "F";  // Fruit
            } else {

                bool print = false;

                for(int k=0;k<nTail;k++){ // Increasing size of the snake
                    if(i==yTail[k] && j==xTail[k]){
                        cout<<"O";
                        print=true;
                    }
                }
                if(!print)cout<<" ";
            }
            if (j == width - 1) {
                cout << "#";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width+1; i++) {
        cout << "#";
    }
    cout << endl;

    cout << "Score:" << score << endl;
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': 
            dir = LEFT; 
            break;
            case 'd': 
            dir = RIGHT; 
            break;
            case 'w': 
            dir = UP; 
            break;
            case 's': 
            dir = DOWN; 
            break;
            case 'x': // exit game
            gameover = true; 
            break;
        }
    }
}

void logic() {

    int prevX = xTail[0];
    int prevY = yTail[0];
    
    xTail[0]=x;
    yTail[0]=y;
    int prev2X,prev2Y;
    for(int i=1;i<nTail;i++){
        prev2X=xTail[i];
        prev2Y=yTail[i];
        xTail[i]=prevX;
        yTail[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }
     
     

    switch (dir) {
        case LEFT:
        x--; 
        break;
        case RIGHT: 
        x++; 
        break;
        case UP: 
        y--; 
        break;
        case DOWN: 
        y++; 
        break;
    }
    // wrap around
    if (x >= width) x = 0; 
    if (x < 0) x = width - 1; 
    if (y >= height) y = 0; 
    if (y < 0) y = height - 1; 

    for(int k=0;k<nTail;k++){
        if(x==xTail[k] && y==yTail[k]){
            gameover=true;
        }
    }

    if (x == fruitX && y == fruitY) {
        score+=10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main() {
    setup();
    while (!gameover) {
        board();
        input();
        logic();
        // Sleep for a short period to control game speed (system-specific)
        Sleep(100);
    }
    return 0;
}
