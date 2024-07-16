#ifndef HANGMAN_H
#define HANGMAN_H

#include<iostream>

class Hangman
{
public:
    Hangman();
    void start();

private:
    const short MAX_ATTEMPTS_ALLOWED = 6;
    short attemptsLeft;
    std::string progress, correctGuesses, incorrectGuesses, correctAnswer;
    bool gameOver, playerWon;

    std::string initProgress(std::string);
    std::string getRandomCountryName();

    char getUserInput();

    void updateGameState(char);
    void initGameState();

    bool isGuessCorrect(char);
    bool hasPlayerWon();
    bool hasPlayerLost();
    bool isGameOver();

    void printHangman();
    void printGuessStats();
    void printProgress();
    void printInstructions();
    void printResult();
    void printBanner();
    void printStage();
    void printHead();
    void printTorso();
    void printLeftHand();
    void printRightHand();
    void printLeftLeg();
    void printRightLeg();

    void clearScreen();
    void updateScreen();
};

#endif
