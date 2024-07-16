#ifndef SOKOBAN_H
#define SOKOBAN_H

#include<iostream>

class Sokoban{
public:
    Sokoban();
    ~Sokoban();
    void start();

private:
    const short ROW=50,COL=50;
    const short ESC=27, SPACE=32, ARROW_KEY=-32;
    const short UP_ARROW=72, LEFT_ARROW=75, RIGHT_ARROW=77, DOWN_ARROW=80;
    char **floorMap;
    short level;

    short pr; // Player's position (row)
    short pc; // Player's position (column)

    short boxCoordinates[10][2];
    short destinationCounter=0;
    short lineCount = 0; // Number of rows in the map

    const char player = 153;
    const char box = (char)254;
    const char destination = 'x';
    const char wall = (char)178;
    const char space = ' ';

    bool loadMap(std::string level);
    bool startLevel(short level);
    bool exitGame();
    void initializePosition();
    void setCursorPosition(short x, short y);

    void updatePosition(short x1,short y1,short x2,short y2,char s);

    void printIntroPage();
    void printBanner();
    void printInstructions();
    void printExitInstructions();
    void printLegend();
    void printMaze();
    void clearScreen();
};

#endif // SOKOBAN_H
