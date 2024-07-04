/*:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.*
 *    Author: Javed Hossain       *
 *    Website: javedhossain.com   *
 *    Date: February 26, 2019     *
 *.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:*/

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<conio.h>
using namespace std;

void structure();
void head();
void body();
void leftHand();
void rightHand();
void leftLeg();
void rightLeg();
void showProgress(string);
bool checkCharInString(string, char);
bool playerWon(string);

int main()
{
    char b1=201,b2=205,b3=187,b4=186,b5=200,b6=188,b7=196;
    string c[148]={"Afghanistan","Albania","Algeria","Argentina","Armenia","Australia","Austria","Azerbaijan",
                   "Bahrain","Bangladesh","Belarus","Belgium","Bhutan","Botswana","Brazil","Bulgaria","Burma","Burundi",
                   "Cambodia","Cameroon","Canada,China","Colombia","Costa Rica","Cuba","Denmark","Dominica",
                   "Dominican Republic","Egypt","Eritrea","Estonia","Ethiopia","Fiji","Finland","France","Georgia",
                   "Germany","Ghana","Greece","Grenada","Guyana","Haiti","Shamsuland","Hong Kong","Hungary","Iceland",
                   "India","Indonesia","Iraq","Iran","Ireland","Israel","Italy","Jamaica","Japan","Jordan","Kazakhstan",
                   "Kenya","Kiribati","North Korea","South Korea","Kuwait","Laos","Latvia","Lebanon","Liberia","Libya",
                   "Liechtenstein","Lithuania","Luxembourg","Macau","Madagascar","Malawi","Malaysia","Maldives","Mali",
                   "Malta","Marshall Islands","Mauritania","Mexico","Micronesia","Moldova","Monaco","Mongolia",
                   "Montenegro","Morocco","Mozambique","Namibia","Nauru","Nepal","Netherlands","New Zealand","Nicaragua",
                   "Niger","Nigeria","Norway","Oman","Pakistan","Palau","Palestine","Panama","Paraguay",
                   "Peru","Philippines","Poland","Portugal","Qatar","Romania","Russia","Rwanda","Saint Lucia","Samoa",
                   "San Marino","Saudi Arabia","Senegal","Serbia","Singapore","Slovakia","Solomon Islands","Somalia",
                   "South Africa","Spain","Sri Lanka","Sudan","Swaziland","Sweden","Switzerland","Syria","Taiwan","Tajikistan",
                   "Tanzania","Thailand","Togo","Tonga","Turkey","Turkmenistan","Tuvalu","Uganda","Ukraine","United Arab Emirates",
                   "United Kingdom","Uruguay","Uzbekistan","Vanuatu","Venezuela","Vietnam","Yemen","Zambia","Zimbabwe"};

    cout<<"\n   "<<b1;for(int i=0;i<19;i++)cout<<b2;cout<<b3<<endl;
    cout<<"   "<<b4<<"   H A N G M A N   "<<b4<<endl;
    cout<<"   "<<b5; for(int i=0;i<19;i++)cout<<b2;cout<<b6<<endl;
    cout<<endl;
    cout<<" INSTRUCTIONS: The computer will choose a country."<<endl;
    cout<<" Try to guess the name of the country (by typing in letters)."<<endl;
    cout<<" If you make more than 5 wrong guesses, you will die. "<<endl;
    cout<<"\n Press any key to start. \n";
    getch();
    char ch;
    bool play=true;
    while(play==true){
        string selectedWord,playersProgress="",correctGuesses="",incorrectGuesses="";
        int l,n,chances=6;
        int gameOver=0;
        char guess;

        srand(time(0));
        n=rand()%148;
        selectedWord=c[n];
        l=selectedWord.size();
        for(int i=0;i<l;i++){
            if(selectedWord[i]!=' ')
                playersProgress=playersProgress+"_";
            else
                playersProgress=playersProgress+" ";
        }

        while(gameOver==0){
            system("cls");
            cout<<"\n   "<<b1;for(int i=0;i<19;i++)cout<<b2;cout<<b3<<endl;
            cout<<"   "<<b4<<"   H A N G M A N   "<<b4<<endl;
            cout<<"   "<<b5; for(int i=0;i<19;i++)cout<<b2;cout<<b6<<endl;

            if(correctGuesses.size()>0 || incorrectGuesses.size()>0){
                cout<<"\n  Correct guesses: "<<correctGuesses<<endl;
                cout<<"  Wrong guesses: "<<incorrectGuesses<<endl;
            }
            cout<<endl;
            if(chances==5) head();
            else if(chances==4) body();
            else if(chances==3) leftHand();
            else if(chances==2) rightHand();
            else if(chances==1) leftLeg();
            else if(chances==0) rightLeg();
            else structure();

            cout<<endl;
            showProgress(playersProgress);
            cout<<endl;

            if(chances==0){
                cout<<"\n  GAME OVER, RETARD!\n";
                cout<<"  Name of the country: "<<selectedWord<<endl;
                gameOver=1;
                break;
            }

            if(playerWon(playersProgress)==true){
                cout<<"\n  YOU WON!\n";
                gameOver=1;
                break;
            }

            do{
                cout<<"\n  Guess a letter:";
                cin>>guess;
                if(guess<'a' || guess>'z')
                    cout<<"\n  Invalid input. Enter a letter between a to z."<<endl;
            }while(guess<'a' || guess>'z');

            int x=0;
            for(int i=0;i<selectedWord.size();i++){
                if(selectedWord[i]==guess){
                    playersProgress[i]=guess;
                    x++;
                }else if(selectedWord[i]==(guess-32)){
                    playersProgress[i]=guess-32;
                    x++;
                }
            }
            if(x>0){
                if(checkCharInString(correctGuesses,guess)==false){
                    correctGuesses=correctGuesses+guess+',';
                }
            }else{
                if(checkCharInString(incorrectGuesses,guess)==false){
                    incorrectGuesses=incorrectGuesses+guess+',';
                    chances--;
                }
            }
        }

        cout<<"\n  Press SPACE to play again or press ESC to quit.";

        while(1){
            if(kbhit()){
                ch=getch();
                if(ch==27){
                    return 0;
                }else if(ch==32 || ch==13){
                    play=true;
                    system("cls");
                    break;
                }
            }
        }
    }

}

bool playerWon(string s){
    int x=0;
    for(int i=0;i<s.size();i++){
        if(s[i]!='_'){
            x++;
        }
    }
    if(x==s.size())return true;
    else return false;
}

bool checkCharInString(string s, char c){
    int x=0;
    for(int i=0;i<s.size();i++){
        if(s[i]==c || s[i]==c-32){
            x++;
        }
    }
    if(x>0)return true;
    else return false;
}

void showProgress(string p){
    cout<<"  ";
    for(int i=0;i<p.size();i++){
        cout<<p[i]<<" ";
    }
}

void structure(){
    cout<<"   _________"<<endl;
    cout<<"    "<<(char)179<<"      "<<(char)179<<endl
        <<"    "<<(char)179<<endl
        <<"    "<<(char)179<<endl
        <<"    "<<(char)179<<endl
        <<"  \\"<<"_"<<(char)179<<"_________/"<<endl;
}

void head(){
    cout<<"   _________"<<endl;
    cout<<"    "<<(char)179<<"      "<<(char)179<<endl
        <<"    "<<(char)179<<"      "<<"O"<<endl
        <<"    "<<(char)179<<endl
        <<"    "<<(char)179<<endl
        <<"  \\"<<"_"<<(char)179<<"_________/"<<endl;
}

void body(){
    cout<<"   _________"<<endl;
    cout<<"    "<<(char)179<<"      "<<(char)179<<endl
        <<"    "<<(char)179<<"      "<<"O"<<endl
        <<"    "<<(char)179<<"      "<<(char)179<<endl
        <<"    "<<(char)179<<endl
        <<"  \\"<<"_"<<(char)179<<"_________/"<<endl;
}

void leftHand(){
    cout<<"   _________"<<endl;
    cout<<"    "<<(char)179<<"      "<<(char)179<<endl
        <<"    "<<(char)179<<"      "<<"O"<<endl
        <<"    "<<(char)179<<"     "<<"/"<<(char)179<<endl
        <<"    "<<(char)179<<endl
        <<"  \\"<<"_"<<(char)179<<"_________/"<<endl;
}

void rightHand(){
    cout<<"   _________"<<endl;
    cout<<"    "<<(char)179<<"      "<<(char)179<<endl
        <<"    "<<(char)179<<"      "<<"O"<<endl
        <<"    "<<(char)179<<"     "<<"/"<<(char)179<<"\\"<<endl
        <<"    "<<(char)179<<endl
        <<"  \\"<<"_"<<(char)179<<"_________/"<<endl;
}

void leftLeg(){
    cout<<"   _________"<<endl;
    cout<<"    "<<(char)179<<"      "<<(char)179<<endl
        <<"    "<<(char)179<<"      "<<"O"<<endl
        <<"    "<<(char)179<<"     "<<"/"<<(char)179<<"\\"<<endl
        <<"    "<<(char)179<<"     "<<"/"<<endl
        <<"  \\"<<"_"<<(char)179<<"_________/"<<endl;
}

void rightLeg(){
    cout<<"   _________"<<endl;
    cout<<"    "<<(char)179<<"      "<<(char)179<<endl
        <<"    "<<(char)179<<"      "<<"O"<<endl
        <<"    "<<(char)179<<"     "<<"/"<<(char)179<<"\\"<<endl
        <<"    "<<(char)179<<"     "<<"/ \\"<<endl
        <<"  \\"<<"_"<<(char)179<<"_________/"<<endl;
}
