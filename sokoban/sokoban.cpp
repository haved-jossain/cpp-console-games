#include "sokoban.h"
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;

Sokoban::Sokoban()
{
    floorMap = new char*[ROW];
    for(int i=0; i<ROW; i++)
    {
        floorMap[i] = new char[COL];
    }
    for(int i=0; i<ROW; i++)
    {
        for(int j=0; j<COL; j++)
        {
            floorMap[i][j] = ' ';
        }
    }
}

Sokoban::~Sokoban()
{
    for(int i=0; i<ROW; i++)
    {
        delete floorMap[i];
    }
    delete floorMap;
}

void Sokoban::start()
{
    printIntroPage();
    if(exitGame())
    {
       return;
    }
    startLevel(0);
    printExitInstructions();
    while(true)
    {
        if(kbhit())
        {
            char inputChar=getch();
            if(inputChar==ESC)
            {
                setCursorPosition(0,lineCount+5);
                break;
            }
            if(inputChar==SPACE)
            {
                startLevel(0);
                printExitInstructions();
            }
            if(inputChar==ARROW_KEY)
            {
                char arrowKeyInput=getch();
                if(arrowKeyInput==UP_ARROW)
                {
                    if(pr>0 && floorMap[pr-1][pc]==space)  // If there is space to move up
                    {
                        updatePosition(pc,pr,pc,pr-1,player);
                        floorMap[pr][pc]=space;
                        pr--;
                        floorMap[pr][pc]=player;

                    }
                    else if(pr>0 && floorMap[pr-1][pc]==box)   // If player is trying to push the box upwards
                    {
                        if(pr>1 && floorMap[pr-2][pc]!=wall && floorMap[pr-2][pc]!=box)  // If there is space to move the box upwards
                        {
                            updatePosition(pc,pr-1,pc,pr-2,box);
                            updatePosition(pc,pr,pc,pr-1,player);
                            floorMap[pr][pc]=space;
                            floorMap[pr-1][pc]=space;
                            pr--;
                            floorMap[pr][pc]=player;
                            floorMap[pr-1][pc]=box;
                        }
                    }
                }
                else if(arrowKeyInput==LEFT_ARROW)
                {
                    if(pc>0 && floorMap[pr][pc-1]==space)  // If there is space to move left
                    {
                        updatePosition(pc,pr,pc-1,pr,player);
                        floorMap[pr][pc]=space;
                        pc--;
                        floorMap[pr][pc]=player;
                    }
                    else if(pc>0 && floorMap[pr][pc-1]==box)   // If player is trying to push the box left
                    {
                        if(pr>1 && floorMap[pr][pc-2]!=wall && floorMap[pr][pc-2]!=box)  // If there is space to move the box left
                        {
                            updatePosition(pc-1,pr,pc-2,pr,box);
                            updatePosition(pc,pr,pc-1,pr,player);
                            floorMap[pr][pc]=space;
                            floorMap[pr][pc-1]=space;
                            pc--;
                            floorMap[pr][pc]=player;
                            floorMap[pr][pc-1]=box;
                        }
                    }
                }
                else if(arrowKeyInput==RIGHT_ARROW)
                {
                    if(pc<COL-1 && floorMap[pr][pc+1]==space)  // If there is space to move right
                    {
                        updatePosition(pc,pr,pc+1,pr,player);
                        floorMap[pr][pc]=space;
                        pc++;
                        floorMap[pr][pc]=player;
                    }
                    else if(pc<COL-1 && floorMap[pr][pc+1]==box)   // If player is trying to push the box right
                    {
                        if(pc<COL-2 && floorMap[pr][pc+2]!=wall && floorMap[pr][pc+2]!=box)  // If there is space to move the box right
                        {
                            updatePosition(pc+1,pr,pc+2,pr,box);
                            updatePosition(pc,pr,pc+1,pr,player);
                            floorMap[pr][pc]=space;
                            floorMap[pr][pc+1]=space;
                            pc++;
                            floorMap[pr][pc]=player;
                            floorMap[pr][pc+1]=box;
                        }
                    }
                }
                else if(arrowKeyInput==DOWN_ARROW)
                {
                    if(pr<ROW-1 && floorMap[pr+1][pc]==space)  // If there is space to move down
                    {
                        updatePosition(pc,pr,pc,pr+1,player);
                        floorMap[pr][pc]=space;
                        pr++;
                        floorMap[pr][pc]=player;
                    }
                    else if(pr<ROW-1 && floorMap[pr+1][pc]==box)   // If player is trying to push the box down
                    {
                        if(pr<ROW-2 && floorMap[pr+2][pc]!=wall && floorMap[pr+2][pc]!=box)  // If there is space to move the box down
                        {
                            updatePosition(pc,pr+1,pc,pr+2,box);
                            updatePosition(pc,pr,pc,pr+1,player);
                            floorMap[pr][pc]=space;
                            floorMap[pr+1][pc]=space;
                            pr++;
                            floorMap[pr][pc]=player;
                            floorMap[pr+1][pc]=box;
                        }
                    }
                }
                int counter = 0;
                for(int i=0; i<destinationCounter; i++)
                {
                    if(floorMap[boxCoordinates[i][0]][boxCoordinates[i][1]]==box)
                    {
                        counter++;
                    }
                }
                if(counter == destinationCounter)
                {
                    setCursorPosition(0,lineCount+1);
                    cout<<" \aLevel complete!"<<endl;
                    printExitInstructions();
                }
            }
        }
    }
}

bool Sokoban::loadMap(string level)
{
    string fileName = level;
    lineCount=0;
    if(ifstream(fileName.c_str()))
    {
        ifstream in(fileName.c_str());
        string line;
        for(int i=0; getline(in,line); i++)
        {
            for(int j=0; j<line.size(); j++)
            {
                floorMap[i][j]=line[j];
            }
            lineCount++;
        }
        in.close();
        return true;
    }
    else
    {
        cout << "Error: Map file missing" << endl;
        return false;
    }
}

void Sokoban::initializePosition()
{
    for(int i=0; i<ROW; i++)
    {
        for(int j=0; j<COL; j++)
        {
            if(floorMap[i][j]=='P')
            {
                pr=i;
                pc=j;
                floorMap[i][j]=player;
            }
            else if(floorMap[i][j]=='B')
            {
                floorMap[i][j]=box;
            }
            else if(floorMap[i][j]=='D')
            {
                floorMap[i][j]=destination;
                boxCoordinates[destinationCounter][0]=i;
                boxCoordinates[destinationCounter][1]=j;
                destinationCounter++;
            }
            else if(floorMap[i][j]=='W')
            {
                floorMap[i][j]=wall;
            }
        }
    }
}

void Sokoban::setCursorPosition(short x, short y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void Sokoban::printMaze()
{
    for(int i=0; i<ROW && i<lineCount; i++)
    {
        for(int j=0; j<COL; j++)
        {
            if(floorMap[i][j]==player)
            {
                cout<<player;
            }
            else if(floorMap[i][j]==box)
            {
                cout<<box;
            }
            else if(floorMap[i][j]==destination)
            {
                cout<<destination;
            }
            else if(floorMap[i][j]==space || floorMap[i][j]==0)
            {
                cout<<space;
            }
            else if(floorMap[i][j]==wall)
            {
                cout<<wall;
            }
        }
        cout<<endl;
    }
}

void Sokoban::updatePosition(short x1,short y1,short x2,short y2,char s)
{
    setCursorPosition(x1,y1);
    cout<<" ";
    setCursorPosition(x2,y2);
    cout<<s;
}

bool Sokoban::startLevel(short level)
{
    clearScreen();
    srand(time(0));
    if(!loadMap("sokoban_level_0.txt"))
        return false;

    initializePosition();
    setCursorPosition(0,0);
    printMaze();
    return true;
}

void Sokoban::printIntroPage()
{
    printBanner();
    printInstructions();
    cout << endl;
    printLegend();
    cout << endl;
}

void Sokoban::printExitInstructions()
{
    setCursorPosition(1,lineCount+2);
    cout<<"ESC = Exit | SPACE = Restart";
}

bool Sokoban::exitGame()
{
    cout<<" Press SPACE to start, ESC to exit game.";
    char inputChar;
    do
    {
        inputChar = getch();
        if(inputChar==ESC)
        {
            return true;
        }
    }
    while(inputChar!=SPACE);

    return false;
}

void Sokoban::printBanner()
{
    cout<<endl;
    cout<<"   "<<(char)201;
    for(int i=0; i<19; i++)
    {
        cout<<(char)205;
    }
    cout<<(char)187<<endl;
    cout<<"   "<<(char)186<<"   S O K O B A N   "<<(char)186<<endl;
    cout<<"   "<<(char)200;
    for(int i=0; i<19; i++)
    {
        cout<<(char)205;
    }
    cout<<(char)188<<endl;
    cout<<endl;
}

void Sokoban::printInstructions()
{
    cout<<" INSTRUCTIONS: "<<endl;
    cout<<" - Use arrow keys to move the warehouse keeper."<<endl;
    cout<<" - You can push the boxes but cannot pull them."<<endl;
    cout<<" - Move all the boxes to positions marked with x."<<endl;
    cout<<" - If you get stuck, restart the level and try again."<<endl;
}

void Sokoban::printLegend()
{
    cout<<" "<<player<<" = Player"<<endl;
    cout<<" "<<box<<" = Box "<<endl;
    cout<<" "<<destination<<" = Box destination"<<endl;
    cout<<" "<<wall<<" = Wall"<<endl;
}

void Sokoban::clearScreen()
{
    system("cls");
}
