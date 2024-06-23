#include<iostream>
#include<cstdlib>
#include<ctime>
#include<conio.h>
#include<windows.h>
#include <fstream>

using namespace std;

// Map
const int R=50,C=50;
char W[R][C] = {};

int pr; // Row index of starting point
int pc; // Column index of starting point

// F contains the coordinates of the box destinations
int F[10][2];
int f=0; // Finishing point counter
int lineCount = 0; // Number of rows in the map

char player = 'X';
char box = (char)254;
char destination = 'o';
char wall = (char)178;
char empty = ' ';

bool loadMap(string level){
    // Checking if file exists
    string fileName = level;
    lineCount=0;
    if(ifstream(fileName.c_str())){
        // open file for reading
        ifstream in(fileName.c_str());
        // reading a line a time from file
        string line;
        for(int i=0;getline(in,line);i++){
            //cout << line << endl;
            for(int j=0;j<line.size();j++){
                W[i][j]=line[j];
            }
            lineCount++;
        }
        // reading complete, closing file
        in.close();
        return true;
    }else{
        system("cls");
        cout << "Map file missing." << endl;
        cout << "Download the map from my website." << endl;
        cout << "Save the file in the same folder as Sokoban.cpp." << endl;
        cout << "Do not change the filename." << endl;
        return false;
    }
}

void initializePosition(){
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            if(W[i][j]=='P'){
                pr=i;pc=j;
                W[i][j]=player;
            }else if(W[i][j]=='B'){
                W[i][j]=box;
            }else if(W[i][j]=='D'){
                W[i][j]=destination;
                F[f][0]=i;
                F[f][1]=j;
                f++;
            }else if(W[i][j]=='W'){
                W[i][j]=wall;
            }
        }
    }
}

void setCursorPosition(int x, int y){
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void printMaze(){
    for(int i=0;i<R && i<lineCount;i++){
        for(int j=0;j<C;j++){
            if(W[i][j]==player){
                cout<<player;
            }else if(W[i][j]==box){
                cout<<box;
            }else if(W[i][j]==destination){
                cout<<destination;
            }else if(W[i][j]==empty || W[i][j]==0){
                cout<<empty;
            }else if(W[i][j]==wall){
                cout<<wall;
            }
        }
        cout<<endl;
    }
}

void updatePosition(int x1,int y1,int x2,int y2,char s){
    setCursorPosition(x1,y1);
    cout<<" ";
    setCursorPosition(x2,y2);
    cout<<s;
}

bool startGame(int level){
    system("cls");
    srand(time(0));
    if(!loadMap("sokoban_level_0.txt"))
        return false;
    setCursorPosition(1,lineCount+2);
    cout<<"Press Esc to exit"<<endl;
    setCursorPosition(1,lineCount+3);
    cout<<"Press Space to restart"<<endl;
    initializePosition();
    setCursorPosition(0,0);
    printMaze();
}

int main()
{
    char b1=201,b2=205,b3=187,b4=186,b5=200,b6=188,b7=196;
    cout<<"\n   "<<b1;for(int i=0;i<19;i++)cout<<b2;cout<<b3<<endl;
    cout<<"   "<<b4<<"   S O K O B A N   "<<b4<<endl;
    cout<<"   "<<b5; for(int i=0;i<19;i++)cout<<b2;cout<<b6<<endl;
    cout<<endl;
    cout<<" INSTRUCTIONS: Try to push the box "<<box<<" and place it over the "<<destination<<"."<<endl;
    cout<<"       Use arrow keys to move the player "<<player<<". You can only push the box "<<box<<". "<<endl;
    cout<<" "<<player<<" = Player"<<endl;
    cout<<" "<<box<<" = Box "<<endl;
    cout<<" "<<destination<<" = Box destination"<<endl;
    cout<<" "<<wall<<" = Wall"<<endl;
    cout<<"\n Press any key to start. Press Esc to quit.\n";
    char c = getch();
    if(c==27)return 0; // User presses Esc, exit program
    if(startGame(0)==false)
        return 0;
    while(1){
        if(kbhit()){ // User pressed a key
            char h=getch();
            if(h==27){
                setCursorPosition(0,lineCount+5);
                break;
            }
            if(h==32){ // Pressed space: restart level
                startGame(0);
            }
            if(h==-32){ // Pressed arrow key
                char k=getch();
                if(k==72){ // Presses up arrow
                    if(pr>0 && W[pr-1][pc]==empty){ // If there is space to move up
                        updatePosition(pc,pr,pc,pr-1,player);
                        W[pr][pc]=empty;
                        pr--;
                        W[pr][pc]=player;

                    }else if(pr>0 && W[pr-1][pc]==box){ // If player is trying to push the box upwards
                        if(pr>1 && W[pr-2][pc]!=wall && W[pr-2][pc]!=box){ // If there is space to move the box upwards
                            updatePosition(pc,pr-1,pc,pr-2,box);
                            updatePosition(pc,pr,pc,pr-1,player);
                            W[pr][pc]=empty;
                            W[pr-1][pc]=empty;
                            pr--;
                            //br--;
                            W[pr][pc]=player;
                            W[pr-1][pc]=box;
                        }
                    }
                }
                else if(k==75){ // Presses left arrow
                    if(pc>0 && W[pr][pc-1]==empty){ // If there is space to move left
                        updatePosition(pc,pr,pc-1,pr,player);
                        W[pr][pc]=empty;
                        pc--;
                        W[pr][pc]=player;
                    }else if(pc>0 && W[pr][pc-1]==box){ // If player is trying to push the box left
                        if(pr>1 && W[pr][pc-2]!=wall && W[pr][pc-2]!=box){ // If there is space to move the box left
                            updatePosition(pc-1,pr,pc-2,pr,box);
                            updatePosition(pc,pr,pc-1,pr,player);
                            W[pr][pc]=empty;
                            W[pr][pc-1]=empty;
                            pc--;
                            //bc--;
                            W[pr][pc]=player;
                            W[pr][pc-1]=box;
                        }
                    }
                }
                else if(k==77){ // Presses right arrow
                    if(pc<C-1 && W[pr][pc+1]==empty){ // If there is space to move right
                        updatePosition(pc,pr,pc+1,pr,player);
                        W[pr][pc]=empty;
                        pc++;
                        W[pr][pc]=player;
                    }else if(pc<C-1 && W[pr][pc+1]==box){ // If player is trying to push the box right
                        if(pc<C-2 && W[pr][pc+2]!=wall && W[pr][pc+2]!=box){ // If there is space to move the box right
                            updatePosition(pc+1,pr,pc+2,pr,box);
                            updatePosition(pc,pr,pc+1,pr,player);
                            W[pr][pc]=empty;
                            W[pr][pc+1]=empty;
                            pc++;
                            //bc++;
                            W[pr][pc]=player;
                            W[pr][pc+1]=box;
                        }
                    }
                }
                else if(k==80){ // Pressed down arrow
                    if(pr<R-1 && W[pr+1][pc]==empty){ // If there is space to move down
                        updatePosition(pc,pr,pc,pr+1,player);
                        W[pr][pc]=empty;
                        pr++;
                        W[pr][pc]=player;
                    }else if(pr<R-1 && W[pr+1][pc]==box){ // If player is trying to push the box down
                        if(pr<R-2 && W[pr+2][pc]!=wall &&  W[pr+2][pc]!=box){ // If there is space to move the box down
                            updatePosition(pc,pr+1,pc,pr+2,box);
                            updatePosition(pc,pr,pc,pr+1,player);
                            W[pr][pc]=empty;
                            W[pr+1][pc]=empty;
                            pr++;
                            //br++;
                            W[pr][pc]=player;
                            W[pr+1][pc]=box;
                        }
                    }
                }
                int counter = 0;
                for(int i=0; i<f; i++){
                    if(W[F[i][0]][F[i][1]]==box){
                        counter++;
                    }
                }
                if(counter == f){
                    setCursorPosition(0,lineCount+1);
                    cout<<" \aLevel complete!"<<endl;
                    setCursorPosition(1,lineCount+2);
                    cout<<"Press Esc to exit"<<endl;
                    setCursorPosition(1,lineCount+3);
                    cout<<"Press Space to restart"<<endl;
                }
            }
        }
    }
    //getch();
}
