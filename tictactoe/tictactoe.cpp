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
#include "tictactoe.h"

TicTacToe::TicTacToe()
{
    grid=new char*[3];
    for(int i=0; i<3; i++)
    {
        grid[i]=new char[3];
    }
}

TicTacToe::~TicTacToe()
{
    for(int i=0; i<3; i++)
    {
        delete grid[i];
    }
    delete grid;
}

void TicTacToe::start()
{
    while(true)
    {
        clearScreen();
        initializeGrid();
        printBanner();
        printGrid();
        selectDifficulty();
        initializeSymbols();
        while(getGameState()==IN_PROGRESS)
        {
            refreshScreen();
            if(playerSymbol=='X')
            {
                playersTurn();
                if(getGameState()==IN_PROGRESS)
                {
                    refreshScreen();
                    aiIsThinking();
                    aisTurn();
                }
            }
            else
            {
                aiIsThinking();
                aisTurn();
                if(getGameState()==IN_PROGRESS)
                {
                    refreshScreen();
                    playersTurn();
                }
            }
        }
        refreshScreen();
        printGameResult();
        if(exitGame())
        {
            std::cout<<std::endl;
            return;
        }
    }
}

bool TicTacToe::exitGame()
{
    std::cout<<"\n   Press ESC to quit, SPACE to play again.";
    while(true)
    {
        char ch=getch();
        if(ch==27)
        {
            return true;
        }
        else if(ch==32)
        {
            return false;
        }
    }
}

void TicTacToe::selectDifficulty()
{
    std::cout<<"\n\n   >> Select difficulty (1 = Easy, 2 = Normal, 3 = Hard): ";
    char userInput;;
    do
    {
        userInput = getch();
    }
    while(userInput != EASY && userInput != NORMAL && userInput != HARD);

    difficulty = userInput;
}

void TicTacToe::refreshScreen()
{
    clearScreen();
    printBanner();
    printGrid();
    printSymbols();
}

void TicTacToe::printSymbols()
{
    std::cout << std::endl << std::endl;
    std::cout << "   Player = " << playerSymbol << std::endl;
    std::cout << "   AI = " << aiSymbol << std::endl;
}

void TicTacToe::initializeGrid()
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            grid[i][j]=' ';
        }
    }
}

void TicTacToe::initializeSymbols()
{
    srand(time(0));
    // 50% chance of player getting first turn
    if(rand()%2==0)
    {
        playerSymbol='X';
        aiSymbol='O';
    }
    else
    {
        playerSymbol='O';
        aiSymbol='X';
    }
}

void TicTacToe::printBanner()
{
    const int BANNER_LENGTH=25;
    std::cout<<"   "<<(char)201;
    for(int i=0; i<BANNER_LENGTH; i++)
    {
        std::cout<<(char)205;
    }
    std::cout<<(char)187<<std::endl;
    std::cout<<"   "<<(char)186<<"       TIC TAC TOE       "<<(char)186<<std::endl;
    std::cout<<"   "<<(char)200;
    for(int i=0; i<BANNER_LENGTH; i++)
    {
        std::cout<<(char)205;
    }
    std::cout<<(char)188<<std::endl<<std::endl;
}

void TicTacToe::printGrid()
{
    const char VLINE=179;
    const char HLINE=196;
    const char CROSS=197;

    std::cout<<std::endl;
    std::cout<<"    "  <<  grid[0][0]<<" "  <<VLINE<<" "<<grid[0][1]<<" "<<VLINE<<  " "  <<grid[0][2]<<" ";
    std::cout<<"      "<<    " "<<7<<" "    <<VLINE<<    " "<<8<<" "     <<VLINE<<    " "<<9<<" "<<std::endl;
    std::cout<<"   "   <<HLINE<<HLINE<<HLINE<<CROSS<<HLINE<<HLINE<<HLINE <<CROSS<<HLINE<<HLINE<<HLINE;
    std::cout<<"      "<<HLINE<<HLINE<<HLINE<<CROSS<<HLINE<<HLINE<<HLINE <<CROSS<<HLINE<<HLINE<<HLINE<<std::endl;
    std::cout<<"    "  <<  grid[1][0]<<" "  <<VLINE<<" "<<grid[1][1]<<" "<<VLINE<<  " "  <<grid[1][2]<<" ";
    std::cout<<"      "<<    " "<<4<<" "    <<VLINE<<    " "<<5<<" "     <<VLINE<<    " "<<6<<" "<<std::endl;
    std::cout<<"   "   <<HLINE<<HLINE<<HLINE<<CROSS<<HLINE<<HLINE<<HLINE <<CROSS<<HLINE<<HLINE<<HLINE;
    std::cout<<"      "<<HLINE<<HLINE<<HLINE<<CROSS<<HLINE<<HLINE<<HLINE <<CROSS<<HLINE<<HLINE<<HLINE<<std::endl;
    std::cout<<"    "  <<  grid[2][0]<<" "  <<VLINE<<" "<<grid[2][1]<<" "<<VLINE<<  " "  <<grid[2][2]<<" ";
    std::cout<<"      "<<    " "<<1<<" "    <<VLINE<<    " "<<2<<" "     <<VLINE<<    " "<<3<<" "<<std::endl;
}

void TicTacToe::playersTurn()
{
    std::cout<<"\n   >> Your turn. Enter position (1-9): ";
    int row, col;
    char userInput;
    do
    {
        userInput = getch();
    }
    while(userInput < '1' || userInput > '9');

    switch(userInput)
    {
    case '1':
        row=2;
        col=0;
        break;
    case '2':
        row=2;
        col=1;
        break;
    case '3':
        row=2;
        col=2;
        break;
    case '4':
        row=1;
        col=0;
        break;
    case '5':
        row=1;
        col=1;
        break;
    case '6':
        row=1;
        col=2;
        break;
    case '7':
        row=0;
        col=0;
        break;
    case '8':
        row=0;
        col=1;
        break;
    case '9':
        row=0;
        col=2;
        break;
    }

    if(grid[row][col]==' ')
    {
        grid[row][col]=playerSymbol;
    }
    else
    {
        std::cout<<"\n   Invalid move."<<std::endl;
        playersTurn();
    }
}

void TicTacToe::aisTurn()
{
    const char A=aiSymbol; // To make lines shorter
    const char P=playerSymbol; // To make lines shorter

    if(difficulty >= EASY)
    {
        // Try to win
        if(     grid[0][0]==A && grid[0][1]==A && grid[0][2]==' ')
        {
            grid[0][2]=A;
            return;
        }
        else if(grid[0][0]==A && grid[0][2]==A && grid[0][1]==' ')
        {
            grid[0][1]=A;
            return;
        }
        else if(grid[0][1]==A && grid[0][2]==A && grid[0][0]==' ')
        {
            grid[0][0]=A;
            return;
        }
        else if(grid[1][0]==A && grid[1][1]==A && grid[1][2]==' ')
        {
            grid[1][2]=A;
            return;
        }
        else if(grid[1][0]==A && grid[1][2]==A && grid[1][1]==' ')
        {
            grid[1][1]=A;
            return;
        }
        else if(grid[1][1]==A && grid[1][2]==A && grid[1][0]==' ')
        {
            grid[1][0]=A;
            return;
        }
        else if(grid[2][0]==A && grid[2][1]==A && grid[2][2]==' ')
        {
            grid[2][2]=A;
            return;
        }
        else if(grid[2][0]==A && grid[2][2]==A && grid[2][1]==' ')
        {
            grid[2][1]=A;
            return;
        }
        else if(grid[2][1]==A && grid[2][2]==A && grid[2][0]==' ')
        {
            grid[2][0]=A;
            return;
        }
        else if(grid[0][0]==A && grid[1][0]==A && grid[2][0]==' ')
        {
            grid[2][0]=A;
            return;
        }
        else if(grid[0][0]==A && grid[2][0]==A && grid[1][0]==' ')
        {
            grid[1][0]=A;
            return;
        }
        else if(grid[1][0]==A && grid[2][0]==A && grid[0][0]==' ')
        {
            grid[0][0]=A;
            return;
        }
        else if(grid[0][1]==A && grid[1][1]==A && grid[2][1]==' ')
        {
            grid[2][1]=A;
            return;
        }
        else if(grid[0][1]==A && grid[2][1]==A && grid[1][1]==' ')
        {
            grid[1][1]=A;
            return;
        }
        else if(grid[1][1]==A && grid[2][1]==A && grid[0][1]==' ')
        {
            grid[0][1]=A;
            return;
        }
        else if(grid[0][2]==A && grid[1][2]==A && grid[2][2]==' ')
        {
            grid[2][2]=A;
            return;
        }
        else if(grid[0][2]==A && grid[2][2]==A && grid[1][2]==' ')
        {
            grid[1][2]=A;
            return;
        }
        else if(grid[1][2]==A && grid[2][2]==A && grid[0][2]==' ')
        {
            grid[0][2]=A;
            return;
        }
        else if(grid[0][0]==A && grid[1][1]==A && grid[2][2]==' ')
        {
            grid[2][2]=A;
            return;
        }
        else if(grid[0][0]==A && grid[2][2]==A && grid[1][1]==' ')
        {
            grid[1][1]=A;
            return;
        }
        else if(grid[1][1]==A && grid[2][2]==A && grid[0][0]==' ')
        {
            grid[0][0]=A;
            return;
        }
        else if(grid[0][2]==A && grid[1][1]==A && grid[2][0]==' ')
        {
            grid[2][0]=A;
            return;
        }
        else if(grid[0][2]==A && grid[2][0]==A && grid[1][1]==' ')
        {
            grid[1][1]=A;
            return;
        }
        else if(grid[1][1]==A && grid[2][0]==A && grid[0][2]==' ')
        {
            grid[0][2]=A;
            return;
        }
    }
    if(difficulty >= NORMAL)
    {
        // Stop the player from winning
        if(     grid[0][0]==P && grid[0][1]==P && grid[0][2]==' ')
        {
            grid[0][2]=A;
            return;
        }
        else if(grid[0][0]==P && grid[0][2]==P && grid[0][1]==' ')
        {
            grid[0][1]=A;
            return;
        }
        else if(grid[0][1]==P && grid[0][2]==P && grid[0][0]==' ')
        {
            grid[0][0]=A;
            return;
        }
        else if(grid[1][0]==P && grid[1][1]==P && grid[1][2]==' ')
        {
            grid[1][2]=A;
            return;
        }
        else if(grid[1][0]==P && grid[1][2]==P && grid[1][1]==' ')
        {
            grid[1][1]=A;
            return;
        }
        else if(grid[1][1]==P && grid[1][2]==P && grid[1][0]==' ')
        {
            grid[1][0]=A;
            return;
        }
        else if(grid[2][0]==P && grid[2][1]==P && grid[2][2]==' ')
        {
            grid[2][2]=A;
            return;
        }
        else if(grid[2][0]==P && grid[2][2]==P && grid[2][1]==' ')
        {
            grid[2][1]=A;
            return;
        }
        else if(grid[2][1]==P && grid[2][2]==P && grid[2][0]==' ')
        {
            grid[2][0]=A;
            return;
        }
        else if(grid[0][0]==P && grid[1][0]==P && grid[2][0]==' ')
        {
            grid[2][0]=A;
            return;
        }
        else if(grid[0][0]==P && grid[2][0]==P && grid[1][0]==' ')
        {
            grid[1][0]=A;
            return;
        }
        else if(grid[1][0]==P && grid[2][0]==P && grid[0][0]==' ')
        {
            grid[0][0]=A;
            return;
        }
        else if(grid[0][1]==P && grid[1][1]==P && grid[2][1]==' ')
        {
            grid[2][1]=A;
            return;
        }
        else if(grid[0][1]==P && grid[2][1]==P && grid[1][1]==' ')
        {
            grid[1][1]=A;
            return;
        }
        else if(grid[1][1]==P && grid[2][1]==P && grid[0][1]==' ')
        {
            grid[0][1]=A;
            return;
        }
        else if(grid[0][2]==P && grid[1][2]==P && grid[2][2]==' ')
        {
            grid[2][2]=A;
            return;
        }
        else if(grid[0][2]==P && grid[2][2]==P && grid[1][2]==' ')
        {
            grid[1][2]=A;
            return;
        }
        else if(grid[1][2]==P && grid[2][2]==P && grid[0][2]==' ')
        {
            grid[0][2]=A;
            return;
        }
        else if(grid[0][0]==P && grid[1][1]==P && grid[2][2]==' ')
        {
            grid[2][2]=A;
            return;
        }
        else if(grid[0][0]==P && grid[2][2]==P && grid[1][1]==' ')
        {
            grid[1][1]=A;
            return;
        }
        else if(grid[1][1]==P && grid[2][2]==P && grid[0][0]==' ')
        {
            grid[0][0]=A;
            return;
        }
        else if(grid[0][2]==P && grid[1][1]==P && grid[2][0]==' ')
        {
            grid[2][0]=A;
            return;
        }
        else if(grid[0][2]==P && grid[2][0]==P && grid[1][1]==' ')
        {
            grid[1][1]=A;
            return;
        }
        else if(grid[1][1]==P && grid[2][0]==P && grid[0][2]==' ')
        {
            grid[0][2]=A;
            return;
        }
    }
    if(difficulty==HARD)
    {
        // Strategize: create a "fork" and trick the player
        if(grid[0][0]==P && grid[1][1]==P && grid[2][2]==A && grid[0][2]==' ')
        {
            grid[0][2]=A;
            return;
        }
        else if(grid[0][0]==P && grid[1][1]==P && grid[2][2]==A && grid[2][0]==' ')
        {
            grid[2][0]=A;
            return;
        }
        else if(grid[0][2]==P && grid[1][1]==P && grid[2][0]==A && grid[0][0]==' ')
        {
            grid[0][0]=A;
            return;
        }
        else if(grid[0][2]==P && grid[1][1]==P && grid[2][0]==A && grid[2][2]==' ')
        {
            grid[2][2]=A;
            return;
        }
        else if(grid[2][0]==P && grid[1][1]==P && grid[0][2]==A && grid[0][0]==' ')
        {
            grid[0][0]=A;
            return;
        }
        else if(grid[2][0]==P && grid[1][1]==P && grid[0][2]==A && grid[2][2]==' ')
        {
            grid[2][2]=A;
            return;
        }
        else if(grid[2][2]==P && grid[1][1]==P && grid[0][0]==A && grid[0][2]==' ')
        {
            grid[0][2]=A;
            return;
        }
        else if(grid[2][2]==P && grid[1][1]==P && grid[0][0]==A && grid[2][0]==' ')
        {
            grid[2][0]=A;
            return;
        }
        // If this is the first/second turn, pick a corner
        else if(grid[0][0]==' ')
        {
            grid[0][0]=A;
            return;
        }
        else if(grid[0][2]==' ')
        {
            grid[0][2]=A;
            return;
        }
        else if(grid[2][0]==' ')
        {
            grid[2][0]=A;
            return;
        }
        else if(grid[2][2]==' ')
        {
            grid[2][2]=A;
            return;
        }
    }

    // No intelligent move to make, so make a random move
    int row, col;
    while(true)
    {
        row=rand()%3;
        col=rand()%3;
        if(grid[row][col]==' ')
        {
            grid[row][col]=A;
            return;
        }
    }
}

int TicTacToe::getRemainingMoves()
{
    int remainingMoves=0;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(grid[i][j]==' ')
            {
                remainingMoves++;
            }
        }
    }
    return remainingMoves;
}

int TicTacToe::getGameState()
{
    if(hasWon(playerSymbol))
    {
        return PLAYER_WON;
    }
    else if(hasWon(aiSymbol))
    {
        return PLAYER_LOST;
    }
    else if(getRemainingMoves()==0)
    {
        return DRAW;
    }
    else
    {
        return IN_PROGRESS;
    }
}

bool TicTacToe::hasWon(const char symbol)
{
    if(   grid[0][0]==symbol && grid[0][1]==symbol && grid[0][2]==symbol
            || grid[1][0]==symbol && grid[1][1]==symbol && grid[1][2]==symbol
            || grid[2][0]==symbol && grid[2][1]==symbol && grid[2][2]==symbol
            || grid[0][0]==symbol && grid[1][1]==symbol && grid[2][2]==symbol
            || grid[0][2]==symbol && grid[1][1]==symbol && grid[2][0]==symbol
            || grid[0][0]==symbol && grid[1][0]==symbol && grid[2][0]==symbol
            || grid[0][1]==symbol && grid[1][1]==symbol && grid[2][1]==symbol
            || grid[0][2]==symbol && grid[1][2]==symbol && grid[2][2]==symbol
      )
    {
        return true;
    }
    return false;
}

void TicTacToe::printGameResult()
{
    int state=getGameState();
    if(state==DRAW)
    {
        std::cout<<"\n   DRAW!      \n";
    }
    else if(state==PLAYER_WON)
    {
        std::cout<<"\n   YOU WON!      \n";
    }
    else if(state==PLAYER_LOST)
    {
        std::cout<<"\n   YOU LOST!      \n";
    }
}

void TicTacToe::clearScreen()
{
    system("cls");
}

void TicTacToe::aiIsThinking()
{
    std::cout<<"\n   >> AI's turn";
    Sleep(250);
    std::cout<<".";
    Sleep(250);
    std::cout<<".";
    Sleep(250);
    std::cout<<".";
    Sleep(250);
}
