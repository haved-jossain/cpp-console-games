/*:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.*
 *    Author: Javed Hossain       *
 *    Website: javedhossain.com   *
 *    Date: February 26, 2019     *
 .:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.*/

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<conio.h>
#include<windows.h>
#include<stdio.h> // For fflush(stdin)
using namespace std;

char T[3][3],P,C;
bool gameOver=false;
bool playerWon=false;
bool computerWon=false;
bool playerLoop=false;
bool computerLoop=false;
bool randomMove=false;
int player=0;
int computer=0;
int p,r,c,x=0;
char b1=201,b2=205,b3=187,b4=186,b5=200,b6=188,b7=196;

void display();
void initialize();
void choose();
void playersMove();
void computersMove();
void checkGame();
void replay();
void playersLoop();
void computersLoop();

int main()
{
    char ch;
    bool play=true;
    while(play==true){
        initialize();
        while(gameOver==false){
            display();
            playersMove();
            display();
            checkGame();
            if(gameOver==false){
                computersMove();
                checkGame();
            }
        }
        cout<<"\n    Press SPACE to play again or press ESC to quit.";
        ch=getch();
        if(ch==27){
            cout<<endl;
            play=false;
        }
    }
}


void display(){
    system("cls");
    cout<<endl;
    cout<<"   "<<b1;for(int i=0;i<27;i++)cout<<b2;cout<<b3<<endl;
    cout<<"   "<<b4<<"        TIC TAC TOE        "<<b4<<endl;
    cout<<"   "<<b5; for(int i=0;i<27;i++)cout<<b2;cout<<b6<<endl<<endl;
    cout<<"    "<<T[0][0]<<" "<<(char)179<<" "<<T[0][1]<<" "<<(char)179<<" "<<T[0][2]<<" ";
    cout<<"      "<<" "<<1<<" "<<(char)179<<" "<<2<<" "<<(char)179<<" "<<3<<" "<<endl;
    cout<<"   "<<(char)196<<(char)196<<(char)196<<(char)197<<(char)196<<(char)196<<(char)196<<(char)197<<(char)196<<(char)196<<(char)196;
    cout<<"      "<<(char)196<<(char)196<<(char)196<<(char)197<<(char)196<<(char)196<<(char)196<<(char)197<<(char)196<<(char)196<<(char)196<<endl;
    cout<<"    "<<T[1][0]<<" "<<(char)179<<" "<<T[1][1]<<" "<<(char)179<<" "<<T[1][2]<<" ";
    cout<<"      "<<" "<<4<<" "<<(char)179<<" "<<5<<" "<<(char)179<<" "<<6<<" "<<endl;
    cout<<"   "<<(char)196<<(char)196<<(char)196<<(char)197<<(char)196<<(char)196<<(char)196<<(char)197<<(char)196<<(char)196<<(char)196;
    cout<<"      "<<(char)196<<(char)196<<(char)196<<(char)197<<(char)196<<(char)196<<(char)196<<(char)197<<(char)196<<(char)196<<(char)196<<endl;
    cout<<"    "<<T[2][0]<<" "<<(char)179<<" "<<T[2][1]<<" "<<(char)179<<" "<<T[2][2]<<" ";
    cout<<"      "<<" "<<7<<" "<<(char)179<<" "<<8<<" "<<(char)179<<" "<<9<<" "<<endl;
}

void initialize(){
    P='X',C='O';
    gameOver=false;
    playerWon=false;
    computerWon=false;
    playerLoop=false;
    computerLoop=false;
    x=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            T[i][j]=' ';
        }
    }
}


void playersMove(){
    cout<<"\n   >> Enter position of "<<P<<" : ";
    cin>>p;
    if(p==1){r=0;c=0;}
    else if(p==2){r=0;c=1;}
    else if(p==3){r=0;c=2;}
    else if(p==4){r=1;c=0;}
    else if(p==5){r=1;c=1;}
    else if(p==6){r=1;c=2;}
    else if(p==7){r=2;c=0;}
    else if(p==8){r=2;c=1;}
    else if(p==9){r=2;c=2;}
    else{
        cout<<"\n   Invalid move. Try again."<<endl;
        cin.clear();
        fflush(stdin);
        playersMove();
        return;
    }

    if(T[r][c]==' '){
        T[r][c]=P;
        x++;
    }else{
        cout<<"\n   Invalid move. Try again."<<endl;
        cin.clear();
        fflush(stdin);
        playersMove();
    }
}

void computersMove(){
    cout<<"\n   << Computer is thinking.";
    Sleep(250);
    cout<<".";
    Sleep(250);
    cout<<".";
    Sleep(250);
    srand(time(0));
    // starting move
    if(rand()%2==0 && T[1][1]==' ') T[1][1]=C;
    // offense moves
    else if(T[0][0]==C && T[0][1]==C && T[0][2]==' ') T[0][2]=C;
    else if(T[0][0]==C && T[0][2]==C && T[0][1]==' ') T[0][1]=C;
    else if(T[0][1]==C && T[0][2]==C && T[0][0]==' ') T[0][0]=C;
    else if(T[1][0]==C && T[1][1]==C && T[1][2]==' ') T[1][2]=C;
    else if(T[1][0]==C && T[1][2]==C && T[1][1]==' ') T[1][1]=C;
    else if(T[1][1]==C && T[1][2]==C && T[1][0]==' ') T[1][0]=C;
    else if(T[2][0]==C && T[2][1]==C && T[2][2]==' ') T[2][2]=C;
    else if(T[2][0]==C && T[2][2]==C && T[2][1]==' ') T[2][1]=C;
    else if(T[2][1]==C && T[2][2]==C && T[2][0]==' ') T[2][0]=C;
    else if(T[0][0]==C && T[1][0]==C && T[2][0]==' ') T[2][0]=C;
    else if(T[0][0]==C && T[2][0]==C && T[1][0]==' ') T[1][0]=C;
    else if(T[1][0]==C && T[2][0]==C && T[0][0]==' ') T[0][0]=C;
    else if(T[0][1]==C && T[1][1]==C && T[2][1]==' ') T[2][1]=C;
    else if(T[0][1]==C && T[2][1]==C && T[1][1]==' ') T[1][1]=C;
    else if(T[1][1]==C && T[2][1]==C && T[0][1]==' ') T[0][1]=C;
    else if(T[0][2]==C && T[1][2]==C && T[2][2]==' ') T[2][2]=C;
    else if(T[0][2]==C && T[2][2]==C && T[1][2]==' ') T[1][2]=C;
    else if(T[1][2]==C && T[2][2]==C && T[0][2]==' ') T[0][2]=C;
    else if(T[0][0]==C && T[1][1]==C && T[2][2]==' ') T[2][2]=C;
    else if(T[0][0]==C && T[2][2]==C && T[1][1]==' ') T[1][1]=C;
    else if(T[1][1]==C && T[2][2]==C && T[0][0]==' ') T[0][0]=C;
    else if(T[0][2]==C && T[1][1]==C && T[2][0]==' ') T[2][0]=C;
    else if(T[0][2]==C && T[2][0]==C && T[1][1]==' ') T[1][1]=C;
    else if(T[1][1]==C && T[2][0]==C && T[0][2]==' ') T[0][2]=C;
    // basic defense moves
    else if(T[0][0]==P && T[0][1]==P && T[0][2]==' ') T[0][2]=C;
    else if(T[0][0]==P && T[0][2]==P && T[0][1]==' ') T[0][1]=C;
    else if(T[0][1]==P && T[0][2]==P && T[0][0]==' ') T[0][0]=C;
    else if(T[1][0]==P && T[1][1]==P && T[1][2]==' ') T[1][2]=C;
    else if(T[1][0]==P && T[1][2]==P && T[1][1]==' ') T[1][1]=C;
    else if(T[1][1]==P && T[1][2]==P && T[1][0]==' ') T[1][0]=C;
    else if(T[2][0]==P && T[2][1]==P && T[2][2]==' ') T[2][2]=C;
    else if(T[2][0]==P && T[2][2]==P && T[2][1]==' ') T[2][1]=C;
    else if(T[2][1]==P && T[2][2]==P && T[2][0]==' ') T[2][0]=C;
    else if(T[0][0]==P && T[1][0]==P && T[2][0]==' ') T[2][0]=C;
    else if(T[0][0]==P && T[2][0]==P && T[1][0]==' ') T[1][0]=C;
    else if(T[1][0]==P && T[2][0]==P && T[0][0]==' ') T[0][0]=C;
    else if(T[0][1]==P && T[1][1]==P && T[2][1]==' ') T[2][1]=C;
    else if(T[0][1]==P && T[2][1]==P && T[1][1]==' ') T[1][1]=C;
    else if(T[1][1]==P && T[2][1]==P && T[0][1]==' ') T[0][1]=C;
    else if(T[0][2]==P && T[1][2]==P && T[2][2]==' ') T[2][2]=C;
    else if(T[0][2]==P && T[2][2]==P && T[1][2]==' ') T[1][2]=C;
    else if(T[1][2]==P && T[2][2]==P && T[0][2]==' ') T[0][2]=C;
    else if(T[0][0]==P && T[1][1]==P && T[2][2]==' ') T[2][2]=C;
    else if(T[0][0]==P && T[2][2]==P && T[1][1]==' ') T[1][1]=C;
    else if(T[1][1]==P && T[2][2]==P && T[0][0]==' ') T[0][0]=C;
    else if(T[0][2]==P && T[1][1]==P && T[2][0]==' ') T[2][0]=C;
    else if(T[0][2]==P && T[2][0]==P && T[1][1]==' ') T[1][1]=C;
    else if(T[1][1]==P && T[2][0]==P && T[0][2]==' ') T[0][2]=C;
    // advanced defense moves 1/3 probability
    else if(rand()%5>0){
        if(T[0][0]==P && T[1][1]==P && T[2][2]==C && T[0][2]==' ') T[0][2]=C;
        else if(T[0][0]==P && T[1][1]==P && T[2][2]==C && T[2][0]==' ') T[2][0]=C;
        else if(T[0][2]==P && T[1][1]==P && T[2][0]==C && T[0][0]==' ') T[0][0]=C;
        else if(T[0][2]==P && T[1][1]==P && T[2][0]==C && T[2][2]==' ') T[2][2]=C;
        else if(T[2][0]==P && T[1][1]==P && T[0][2]==C && T[0][0]==' ') T[0][0]=C;
        else if(T[2][0]==P && T[1][1]==P && T[0][2]==C && T[2][2]==' ') T[2][2]=C;
        else if(T[2][2]==P && T[1][1]==P && T[0][0]==C && T[0][2]==' ') T[0][2]=C;
        else if(T[2][2]==P && T[1][1]==P && T[0][0]==C && T[2][0]==' ') T[2][0]=C;
        else{
        // Random move
            int r=rand()%3;
            if(r==0){
                for(int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        if(T[i][j]==' '){
                            T[i][j]=C;
                            x++;
                            return;
                        }
                    }
                }
            }else if(r==1){
                for(int i=0;i<3;i++){
                    for(int j=0;j<3;j++){
                        if(T[j][i]==' '){
                            T[j][i]=C;
                            x++;
                            return;
                        }
                    }
                }
            }else{
                for(int i=2;i>=0;i--){
                    for(int j=2;j>=0;j--){
                        if(T[i][j]==' '){
                            T[i][j]=C;
                            x++;
                            return;
                        }
                    }
                }
            }
        }
    }else{
        // Random move
        int r=rand()%3;
        if(r==0){
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(T[i][j]==' '){
                        T[i][j]=C;
                        x++;
                        return;
                    }
                }
            }
        }else if(r==1){
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(T[j][i]==' '){
                        T[j][i]=C;
                        x++;
                        return;
                    }
                }
            }
        }else{
            for(int i=2;i>=0;i--){
                for(int j=2;j>=0;j--){
                    if(T[i][j]==' '){
                        T[i][j]=C;
                        x++;
                        return;
                    }
                }
            }
        }
    }
    x++;
}

void checkGame(){
    if(T[0][0]==C && T[0][1]==C && T[0][2]==C){computerWon=true;}
    else if(T[1][0]==C && T[1][1]==C && T[1][2]==C){computerWon=true;}
    else if(T[2][0]==C && T[2][1]==C && T[2][2]==C){computerWon=true;}
    else if(T[0][0]==C && T[1][1]==C && T[2][2]==C){computerWon=true;}
    else if(T[0][2]==C && T[1][1]==C && T[2][0]==C){computerWon=true;}
    else if(T[0][0]==C && T[1][0]==C && T[2][0]==C){computerWon=true;}
    else if(T[0][1]==C && T[1][1]==C && T[2][1]==C){computerWon=true;}
    else if(T[0][2]==C && T[1][2]==C && T[2][2]==C){computerWon=true;}

    if(T[0][0]==P && T[0][1]==P && T[0][2]==P){playerWon=true;}
    else if(T[1][0]==P && T[1][1]==P && T[1][2]==P){playerWon=true;}
    else if(T[2][0]==P && T[2][1]==P && T[2][2]==P){playerWon=true;}
    else if(T[0][0]==P && T[1][1]==P && T[2][2]==P){playerWon=true;}
    else if(T[0][2]==P && T[1][1]==P && T[2][0]==P){playerWon=true;}
    else if(T[0][0]==P && T[1][0]==P && T[2][0]==P){playerWon=true;}
    else if(T[0][1]==P && T[1][1]==P && T[2][1]==P){playerWon=true;}
    else if(T[0][2]==P && T[1][2]==P && T[2][2]==P){playerWon=true;}

    if(x==9) {gameOver=true;}

    if(playerWon==true) {
            gameOver=true;
            display();
            cout<<"\n\n    YOU WON!     \n\n";
            player++;
            return;
    }
    if(computerWon==true) {
            gameOver=true;
            display();
            cout<<"\n\n    YOU LOST!     \n\n";
            computer++;
            return;
    }
    if(gameOver==true) {
            display();
            cout<<"\n\n    DRAW!      \n\n";
            return;
    }
}
