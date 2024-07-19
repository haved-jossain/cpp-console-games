/*:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.*
 *    Author: Javed Hossain       *
 *    Website: javedhossain.com   *
 *    Date: February 26, 2019     *
 *.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:*/

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<conio.h>
#include "hangman.h"

Hangman::Hangman()
{
    initGameState();
}

void Hangman::start()
{
    clearScreen();
    printBanner();
    printInstructions();
    getch();
    while(true)
    {
        while(!isGameOver())
        {
            updateScreen();
            updateGameState(getUserInput());
        }
        updateScreen();
        printResult();

        std::cout<<"\n  Press ESC to quit, SPACE to play again.";
        char ch=getch();
        if(ch == 27)
        {
            std::cout<<std::endl;
            return;
        }
        else if(ch == 32)
        {
            initGameState();
            clearScreen();
            printBanner();
        }
    }
}

void Hangman::initGameState(){
    attemptsLeft = MAX_ATTEMPTS_ALLOWED;
    correctGuesses = "";
    incorrectGuesses = "";
    correctAnswer = getRandomCountryName();
    progress = initProgress(correctAnswer);
    gameOver = false;
    playerWon = false;
}

void Hangman::updateScreen()
{
    clearScreen();
    printBanner();
    printGuessStats();
    printHangman();
    printProgress();
}

void Hangman::clearScreen()
{
    system("cls");
}

bool Hangman::isGameOver()
{
    if(hasPlayerWon() || hasPlayerLost())
    {
        return true;
    }

    return false;
}

void Hangman::updateGameState(char userInputLowercase)
{
    const int CASE_DIFFERENCE = 32;
    bool correctGuess = false;
    // User input is always taken as lowercase but the first letter
    // of a country name is uppercase, so we need to convert the input.
    // This, of course, could  have been handled differently.
    int userInputUpperCase = userInputLowercase - CASE_DIFFERENCE;
    for(int i=0; i<correctAnswer.size(); i++)
    {
        if(correctAnswer[i] == userInputLowercase
           || correctAnswer[i] == userInputUpperCase)
        {
            progress[i] = correctAnswer[i];
            correctGuess = true;
            if(correctGuesses.find(userInputLowercase) == std::string::npos)
            {
                correctGuesses = correctGuesses+userInputLowercase+',';
            }
        }
    }

    if(!correctGuess
       && incorrectGuesses.find(userInputLowercase) == std::string::npos)
    {
        incorrectGuesses=incorrectGuesses+userInputLowercase+',';
        attemptsLeft--;
    }
}

bool Hangman::hasPlayerLost()
{
    if(attemptsLeft == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Hangman::printHangman()
{
    switch(attemptsLeft)
    {
    case 5:
        printHead();
        break;
    case 4:
        printTorso();
        break;
    case 3:
        printLeftHand();
        break;
    case 2:
        printRightHand();
        break;
    case 1:
        printLeftLeg();
        break;
    case 0:
        printRightLeg();
        break;
    default:
        printStage();
    }
}

void Hangman::printResult()
{
    if(hasPlayerWon())
    {
        std::cout<<"\n  YOU WON!\n";
    }
    else
    {
        std::cout<<"\n  YOU LOST!\n";
        std::cout<<"\n  Correct answer: "<<correctAnswer<<std::endl;
    }
}

void Hangman::printGuessStats()
{
    std::cout<<"\n  Correct guesses: "<<correctGuesses<<std::endl;
    std::cout<<"  Wrong guesses: "<<incorrectGuesses<<std::endl;
    std::cout<<std::endl;
}

// This function prints underscores based on the number
// of letters in the name of the selected country
std::string Hangman::initProgress(std::string correctAnswer)
{
    std::string playersProgress = "";
    for(int i = 0; i < correctAnswer.size(); i++)
    {
        if(correctAnswer[i] != ' ')
        {
            playersProgress = playersProgress + "_";
        }
        else
        {
            playersProgress = playersProgress + " ";
        }
    }
    return playersProgress;
}

char Hangman::getUserInput()
{
    char userInput;
    do
    {
        std::cout<<"\n  Guess a letter: ";
        std::cin>>userInput;
        // Only lowercase letters are accepted
        if(userInput<'a' || userInput>'z')
        {
            std::cout<<"\n  Invalid input. Enter a \
            lowercase letter between a to z."<<std::endl;
        }

    }
    while(userInput<'a' || userInput>'z');
    return userInput;
}

std::string Hangman::getRandomCountryName()
{
    const int NUMBER_OF_COUNTRIES = 148;
    std::string countryList[NUMBER_OF_COUNTRIES]= {"Afghanistan","Albania",
    "Algeria","Argentina","Armenia","Australia","Austria","Azerbaijan",
    "Bahrain","Bangladesh","Belarus","Belgium","Bhutan","Botswana","Brazil",
    "Bulgaria","Burma","Burundi","Cambodia","Cameroon","Canada,China",
    "Colombia","Costa Rica","Cuba","Denmark","Dominica","Dominican Republic",
    "Egypt","Eritrea","Estonia","Ethiopia","Fiji","Finland","France","Georgia",
    "Germany","Ghana","Greece","Grenada","Guyana","Haiti","Hawai'i",
    "Hong Kong","Hungary","Iceland","India","Indonesia","Iraq","Iran","Ireland",
    "Israel","Italy","Jamaica","Japan","Jordan","Kazakhstan","Kenya","Kiribati",
    "North Korea","South Korea","Kuwait","Laos","Latvia","Lebanon","Liberia",
    "Libya","Liechtenstein","Lithuania","Luxembourg","Macau","Madagascar",
    "Malawi","Malaysia","Maldives","Mali","Malta","Marshall Islands",
    "Mauritania","Mexico","Micronesia","Moldova","Monaco","Mongolia",
    "Montenegro","Morocco","Mozambique","Namibia","Nauru","Nepal","Netherlands",
    "New Zealand","Nicaragua","Niger","Nigeria","Norway","Oman","Pakistan",
    "Palau","Palestine","Panama","Paraguay","Peru","Philippines","Poland",
    "Portugal","Qatar","Romania","Russia","Rwanda","Saint Lucia","Samoa",
    "San Marino","Saudi Arabia","Senegal","Serbia","Singapore","Slovakia",
    "Solomon Islands","Somalia","South Africa","Spain","Sri Lanka","Sudan",
    "Swaziland","Sweden","Switzerland","Syria","Taiwan","Tajikistan","Tanzania",
    "Thailand","Togo","Tonga","Turkey","Turkmenistan","Uganda","Ukraine",
    "United Arab Emirates","United Kingdom","United States","Uruguay",
    "Uzbekistan","Vanuatu","Venezuela","Vietnam","Yemen","Zambia","Zimbabwe"};

    srand(time(0));
    return countryList[rand() % NUMBER_OF_COUNTRIES];
}

void Hangman::printInstructions()
{
    std::cout<<"\n INSTRUCTIONS: A country will be chosen at random."<<std::endl;
    std::cout<<" Try to guess the letters in the name of the country."<<std::endl;
    std::cout<<" If you make more than 5 wrong guesses, you will die."<<std::endl;
    std::cout<<"\n Press any key to start.";
}

void Hangman::printBanner()
{
    const int BANNER_LENGTH = 25;
    std::cout << "\n";
    std::cout << " " << (char)201;
    for(int i=0; i<BANNER_LENGTH; i++)
    {
        std::cout << (char)205;
    }
    std::cout << (char)187;
    std::cout << "\n " << (char)186 << "      H A N G M A N      " << (char)186;
    std::cout << "\n " << (char)200;
    for(int i=0; i<BANNER_LENGTH; i++)
    {
        std::cout << (char)205;
    }
    std::cout << (char)188 << std::endl;
}

bool Hangman::hasPlayerWon()
{
    int correctGuesses = 0;
    for(int i=0; i<correctAnswer.size(); i++)
    {
        if(progress[i] != '_')
        {
            correctGuesses++;
        }
    }
    if(correctGuesses == correctAnswer.size())
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool Hangman::isGuessCorrect(char guess)
{
    if(correctAnswer.find(guess) != std::string::npos
       || correctAnswer.find(guess-32) != std::string::npos)
    {
        return true;
    }

    return false;
}

void Hangman::printProgress()
{
    std::cout<<"\n  ";
    for(int i=0; i<progress.size(); i++)
    {
        std::cout<<progress[i]<<" ";
    }
    std::cout<<std::endl;
}

void Hangman::printStage()
{
    std::cout<<"   _________"<<std::endl;
    std::cout<<"    "<<(char)179<<"      "<<(char)179<<std::endl
             <<"    "<<(char)179<<std::endl
             <<"    "<<(char)179<<std::endl
             <<"    "<<(char)179<<std::endl
             <<"  \\"<<"_"<<(char)179<<"_________/"<<std::endl;
}

void Hangman::printHead()
{
    std::cout<<"   _________"<<std::endl;
    std::cout<<"    "<<(char)179<<"      "<<(char)179<<std::endl
             <<"    "<<(char)179<<"      "<<"O"<<std::endl
             <<"    "<<(char)179<<std::endl
             <<"    "<<(char)179<<std::endl
             <<"  \\"<<"_"<<(char)179<<"_________/"<<std::endl;
}

void Hangman::printTorso()
{
    std::cout<<"   _________"<<std::endl;
    std::cout<<"    "<<(char)179<<"      "<<(char)179<<std::endl
             <<"    "<<(char)179<<"      "<<"O"<<std::endl
             <<"    "<<(char)179<<"      "<<(char)179<<std::endl
             <<"    "<<(char)179<<std::endl
             <<"  \\"<<"_"<<(char)179<<"_________/"<<std::endl;
}

void Hangman::printLeftHand()
{
    std::cout<<"   _________"<<std::endl;
    std::cout<<"    "<<(char)179<<"      "<<(char)179<<std::endl
             <<"    "<<(char)179<<"      "<<"O"<<std::endl
             <<"    "<<(char)179<<"     "<<"/"<<(char)179<<std::endl
             <<"    "<<(char)179<<std::endl
             <<"  \\"<<"_"<<(char)179<<"_________/"<<std::endl;
}

void Hangman::printRightHand()
{
    std::cout<<"   _________"<<std::endl;
    std::cout<<"    "<<(char)179<<"      "<<(char)179<<std::endl
             <<"    "<<(char)179<<"      "<<"O"<<std::endl
             <<"    "<<(char)179<<"     "<<"/"<<(char)179<<"\\"<<std::endl
             <<"    "<<(char)179<<std::endl
             <<"  \\"<<"_"<<(char)179<<"_________/"<<std::endl;
}

void Hangman::printLeftLeg()
{
    std::cout<<"   _________"<<std::endl;
    std::cout<<"    "<<(char)179<<"      "<<(char)179<<std::endl
             <<"    "<<(char)179<<"      "<<"O"<<std::endl
             <<"    "<<(char)179<<"     "<<"/"<<(char)179<<"\\"<<std::endl
             <<"    "<<(char)179<<"     "<<"/"<<std::endl
             <<"  \\"<<"_"<<(char)179<<"_________/"<<std::endl;
}

void Hangman::printRightLeg()
{
    std::cout<<"   _________"<<std::endl;
    std::cout<<"    "<<(char)179<<"      "<<(char)179<<std::endl
             <<"    "<<(char)179<<"      "<<"O"<<std::endl
             <<"    "<<(char)179<<"     "<<"/"<<(char)179<<"\\"<<std::endl
             <<"    "<<(char)179<<"     "<<"/ \\"<<std::endl
             <<"  \\"<<"_"<<(char)179<<"_________/"<<std::endl;
}
