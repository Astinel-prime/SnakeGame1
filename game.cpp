#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

bool gameover;
const int width=20,height=20;

int x,y,fruitX,fruitY,score;
int tailX[100],tailY[100];
int nTail=0;
enum eDirection{STOP=0,UP,DOWN,LEFT,RIGHT};
eDirection dir;

void HideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void setup(){
    HideCursor();
    gameover=false;
    dir= STOP;
    x=width/2;
    y=height/2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score=0;
    
 }

void draw(){
    system("cls");
    cout<<"Snake Game"<<endl;
    for(int i = 0; i < width+2; i++){
        cout << "#";
    }
    cout<<endl;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(j==0){
                cout<<"#";
            }
            if(i==y && j==x){
                cout<<"O";
            }
            else if(i==fruitY && j==fruitX){
                cout<<"*";
            }
            else {
                bool print=false;
                for(int k=0;k<nTail;k++){
                    if(tailX[k]==j&&tailY[k]==i){
                    cout<<"o";
                    print=true;
                    break;
                    }
                }
                if(!print) cout<<" ";
            }
           if(j==width-1){
            cout<<"#";
           }
        }
        cout<<endl;
    }
    for(int i = 0; i < width+2; i++){
        cout << "#";
    }
    cout<<endl;
    cout<< "Score: "<<score<<endl;
}

void input(){

    if(_kbhit()){
        switch (_getch()){
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir= RIGHT;
                break;
            case 'w':
                dir= UP;
                break;
            case 's':
                dir= DOWN;
                break;
            case 'x':
                gameover= true;
                break;
        }
    }
}

void logic(){
    int prevX = tailX[0],prevY = tailY[0];
    int prev2X,prev2Y;
    tailX[0]=x; tailY[0]=y;
    for(int i = 1; i < nTail; i++){
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }


    switch (dir){
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
    //if(x<=0||x>=width||y<=0||y>=height) gameover=true;
    if(x>=width) x=0; else if(x<0) x=width-1;
    if(y>=height) y=0; else if(y<0) y=height-1;

    for(int i=0;i<nTail;i++){
        if(x==tailX[i]&&y==tailY[i]) gameover=true;
    }
    if(x==fruitX && y==fruitY){
        
        score+=10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main(){
    setup();
    while(!gameover){
        draw();
        input();
        logic();
        Sleep(80);
    }
}
