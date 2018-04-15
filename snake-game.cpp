#include <iostream>
#include <stdlib.h>
#include <conio.h>

using namespace std;

bool gameOver;
const int width  = 70;
const int height = 20;

//Position
int x;
int y;

//Fruit position
int fruitX;
int fruitY;

//score
int score;

//tail:
int tailX[100];
int tailY[100];
int nTail;

enum eDirection{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;



void setup(){
    gameOver = false;
    dir = STOP;

    //set position to the center of the map
    x = width / 2;
    y = height / 2;

    //set a random fruit position
    fruitX = rand() % width;
    fruitY = rand() % height;

    //initial score is equal to 0
    score = 0;
}
void draw(){

    system("cls"); // system("clear"); in linux
    for( int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;

    //Print the map:
    for( int i = 0; i < height; i++ ){
        for( int j = 0; j < width; j++ ){
            if( j == 0 )
                cout << "#";
            if( i == y && j == x )
                cout << "O";
            else if( i == fruitY && j == fruitX ) // print the fruit
                cout << "F";
            else{
                bool print = false;
                for ( int k = 0; k < nTail; k++ ){

                    if( tailX[k] == j && tailY[k] == i ){
                        cout << "o";
                        print  = true;
                    }
                }
                 if(  !print )
                    cout << " ";


            }


            if( j == (width - 1) )
                cout << "#";
        }
        cout << endl;
    }


    for( int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;

}

void input(){
    if( _kbhit() ){ // return true if a key is pressed
        switch(_getch()){//get key that was pressed
            case 'a':
                dir = LEFT; // direction gonna be left
                break;
            case 'd':
                dir = RIGHT; // direction gonna be right
                break;
            case 'w':
                dir = UP; // direction gonna be UP
                break;
            case 's':
                dir = DOWN; // direction gonna be Down
                break;
            case 'x':
                gameOver = true; // case press X, game will be finished
                break;
            default://any other key
                break;
        }
    }
}

void logic(){

    int prevX = tailX[0];
    int prevY = tailY[0];

    int prev2X;
    int prev2Y;

    //the first follow the head
    tailX[0] = x;
    tailY[0] = y;

    //tail follows the head
    for( int i = 1; i < nTail; i++ ){
        prev2X   = tailX[i];
        prev2Y   = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX    = prev2X;
        prevY    = prev2Y;
    }
    switch(dir){ // switch direction:
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
        default:
            break;
    }

    /*
        With this code, the game ends when you hit the walls:

        if( x > width || x < 0 ||y > heigth || y < 0)//if i hit the wall
            gameOver = true; //game end
    */

    /* With this code, the snake can cross the walls */
    if ( x >= width )
        x = 0;
    else if ( x < 0 )
        x = width - 1;
    if ( y >= height )
        y = 0;
    else if ( y < 0 )
        y = height - 1;
    /* cross the wall ends here */

    for ( int i = 0; i < nTail; i++ )
        if ( tailX[i] == x && tailY[i] == y )
            gameOver = true;
    if( x ==  fruitX && y == fruitY ){ // if i eat the fruit
        score += 10; //increase the score

        //set a random fruit position
        fruitX = rand() % width;
        fruitY = rand() % height;

        //increase the tail by 1
        nTail++;
    }
}


int main(){
    setup(); // game configs
    while(!gameOver){ // while the game dont end:
        draw();
        input();
        logic();

        //sleep(10);
    }
    return 0;
}
