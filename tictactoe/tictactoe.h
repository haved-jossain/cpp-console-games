#ifndef TICTACTOE_H
#define TICTACTOE_H

class TicTacToe
{
public:
    TicTacToe();
    ~TicTacToe();
    void start();
    void selectDifficulty();

private:
    char **grid;
    char playerSymbol;
    char aiSymbol;
    int difficulty;

    // Game states
    const int DRAW=1, PLAYER_WON=2, PLAYER_LOST=3, IN_PROGRESS=4;
    // Difficulty levels
    const char EASY='1', NORMAL='2', HARD='3';

    void initializeGrid();
    void initializeSymbols();

    int getGameState();
    int getRemainingMoves();
    bool hasWon(char symbol);
    bool exitGame();

    void playersTurn();
    void aisTurn();

    void printGrid();
    void printBanner();
    void printGameResult();
    void clearScreen();
    void aiIsThinking();
    void printSymbols();
    void refreshScreen();
};

#endif
