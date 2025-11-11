//wordle
#include <iostream>
using namespace std;
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <set>
#include <vector>
#include <thread>
#include <string>
#include <typeinfo>
#include <unistd.h>
#include <algorithm>
#include <cctype>
#include <iterator>



//functions
//getting the words
// Function to load all words from file into a set
set <string> getWordleWords() {
    set <string> goodWords;       // Create empty set
    set <string> newWords;
    ifstream file("valid-wordle-words.txt");    // Open file
    string word;                   // Variable to hold each word
    
    // Read each word from file and add to set
    while (file >> word) {
        goodWords.insert(word);             // Add word to set
    }

    //capitalizing
    for (const std::string& word : goodWords) {
        std::string upperWord = word; // Create a modifiable copy
        for (char& c : upperWord) {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
        newWords.insert(upperWord);
    }
    return newWords;                       // Return the complete set
}

//answers
set <string> getWordleAnswers() {
    set <string> goodWords;       // Create empty set
    set <string> newWords;
    ifstream file("valid-wordle-answers.txt");    // Open file
    string word;                   // Variable to hold each word
    
    // Read each word from file and add to set
    while (file >> word) {
        goodWords.insert(word);             // Add word to set
    }

    //capitalizing
    for (const std::string& word : goodWords) {
        std::string upperWord = word; // Create a modifiable copy
        for (char& c : upperWord) {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
        newWords.insert(upperWord);
    }
    return newWords;                       // Return the complete set
}

//secret
vector <string> getWords(){
    vector <string> secretWords;
    string word;
    ifstream file ("secret.txt");
    while (file >> word){
        secretWords.push_back(word);
    }
    for (int i=0; i<secretWords.size(); i++){
        word=secretWords[i];
        for (int j=0; j<word.length(); j++){
            word[j]=toupper(word[j]);
        }
        secretWords[i]=word;
    }
    return secretWords;
}

//getting a random answer
string randomWord(set <string> wordleAnswers){
    auto it = wordleAnswers.begin();

    // Advance the iterator to the random spot
    advance(it, rand()%wordleAnswers.size()); 

    //returning answer
    return *it;
}

//for the alphabet, cheks what letter exists
int whatLetter(int i, string word){
    int number=-1;
    //cout<<"In function";
    if (word[i]=='Q'){
        number= 0;
    } else if (word[i]=='W'){
        number= 1;
    } else if (word[i]=='E'){
        number= 2;
    } else if (word[i]=='R'){
        number= 3;
    } else if (word[i]=='T'){
        number= 4;
    } else if (word[i]=='Y'){
        number= 5;
    } else if (word[i]=='U'){
        number= 6;
    } else if (word[i]=='I'){
        number= 7;
    } else if (word[i]=='O'){
        number= 8;
    } else if (word[i]=='P'){
        number= 9;
    } else if (word[i]=='A'){
        number= 10;
    } else if (word[i]=='S'){
        number= 11;
    } else if (word[i]=='D'){
        number= 12;
    } else if (word[i]=='F'){
        number= 13;
    } else if (word[i]=='G'){
        number= 14;
    } else if (word[i]=='H'){
        number= 15;
    } else if (word[i]=='J'){
        number= 16;
    } else if (word[i]=='K'){
        number= 17;
    } else if (word[i]=='L'){
        number= 18;
    } else if (word[i]=='Z'){
        number= 19;
    } else if (word[i]=='X'){
        number= 20;
    } else if (word[i]=='C'){
        number= 21;
    } else if (word[i]=='V'){
        number= 22;
    } else if (word[i]=='B'){
        number= 23;
    } else if (word[i]=='N'){
        number= 24;
    } else if (word[i]=='M'){
        number= 25;
    } else {
        cout<<"Hmm?";
    }
    return number;
}

//puts to capital letters
void capitalize(string &word){
    for (int i=0; i<word.length(); i++){
        word[i]=toupper(word[i]);
    }
}

//checks for double or triple letters in the answer
void hasMultiple (string answer, string &doubles, string &triples){
    triples="";
    doubles="";
    int isMulti=-1;
    string letter;
    for (int i='A'; i<='Z'; i++){
        isMulti=-1;
        isMulti= count(answer.begin(), answer.end(), i);
        if (isMulti==3){
            letter=i;
            triples.append(letter);
        } else if (isMulti==2){
            letter=i;
            doubles.append(letter);
        }
    }
}


//checks if is a word
bool isWord(string word, string letters, set <string> wordleWords){
    int numLetters=0;
    if (word.length()!=5){
        return false;
    } else {
        for (int i=0; i<26; i++){
            for (int j=0; j<5; j++){
                if (word[j]!=letters[i]){
                    numLetters+=1;
                }
            }
        }
        if (numLetters!=125){
            return false;
        } else {
            if (wordleWords.find(word)!=wordleWords.end()){
                return true;
            } else {
                return false;
            }
        }
    }
}

//checks if letter is in the word and where
int isThere(string word, string answer){
    int greens=-1;
    for (int i=0;i<5+1;i++){
        if (word[i]==answer[i]){
            printf("\033[30;32m");
            cout<<word[i];
            greens+=1;
        } else {
            printf("\033[30;91m");
            cout<<word[i];            
        }
    }
    return greens;
}

//easter egg
void funWords(string guess, bool &discovered, int &funFound, vector <string> &wordsFound, int &funTotal, int &guessNum){
    vector <string> words=getWords();
    capitalize(guess);
    string word; 
    int num=0;
    funTotal=words.size();

    for (int j=0; j<funTotal; j++){
        //found
        if (guess==words[j]){
            //updating
            for (int i=0; i<wordsFound.size(); i++){
                if (guess!=wordsFound[i]){
                    num++;
                }
            }
            //showing congrats
            if (discovered==false){
                cout<<"Congratulations! \nYou found the easter egg! \nThere are "<<funTotal<<" different easter egg words. \nTry to find them all!\nThe first time you find a word it doesn't count as a guess, but it does still show you the output.";
                wordsFound.push_back(guess);
                funFound++;
                guessNum--;
            } else if (num==wordsFound.size()){
                cout<<"You found another word!\nGood job.";
                wordsFound.push_back(guess);
                funFound++;
                guessNum--;
            } else {
                cout<<"Not a new word, but keep going!";
            }
            cout<<"\nSo far you have found "<<funFound<<"/"<<funTotal;
            usleep(5000000);
            cout<<"\n\nEnter anything to continue with the game: ";
            cin>>word;
            discovered=true;   
        }
    }
}




//if the letter is in the word
int inWord (string guess, string answer, string &alphabet, string &word, int &won, int wordNum, vector <string> &completed, string doubles, string triples, string gDouble, string gTriple){
    //variabels
    bool yellow;
    int greens=0;
    word.append("\n  ");
    //which are already done for multi-lettered words
    string yellowed="";
    string green="";
    //edited guesses
    string eGuess;
    string eGuess2;
    string eAnswer;


    //going through the letters of the guess
    for (int j=0; j<5; j++){
        yellow=false;
        string letter;
        //checking correct
        if (guess[j]==answer[j]){
            //having the colours be in a variables
            letter=guess[j];
            word.append("\033[0;32m"+letter);
            greens+=1;
            alphabet.insert(alphabet.find(letter), "\033[0;32m");
            green.append(letter);
            //alphabet[whatLetter(j, guess)]="\033[100;32m"+alphabet[whatLetter(j, guess)];   
            //greening(j, guess, alphabet);
            if (greens==5){
                completed.push_back(guess);
            }
        } else {
            //looping to check yellow
            for( int i=0; i<5; i++){
                if (answer[i]==guess[j]&&i!=j&&!yellow) {
                    //if the guess doesn't have double or triples, the guess and answer has doubles, the guess and aswer has triples, the guess has doubles but the answer has triples
                    if ((gDouble.find(answer[i])>6&&gTriple.find(answer[i])>6)||(gDouble.find(answer[i])<6&&doubles.find(answer[i])<6)||(triples.find(answer[i])<6&&gTriple.find(answer[i])<6)||(gDouble.find(answer[i])<6&&triples.find(answer[i])<6)){
                        letter=guess[j];
                        word.append("\033[0;93m"+letter);
                        if (alphabet.substr(alphabet.find(letter)-3,3)!="32m"){
                            alphabet.insert(alphabet.find(letter), "\033[0;93m");
                        }      
                    } else if (gDouble.find(answer[i])<6){
                        guess.replace(guess.find(answer[i]),1,"1");
                        //if the second location isn't green, and the first location isn't green
                        if (guess.find(answer[i])!=answer.find(answer[i])&&guess.find(answer[i])<6&&green.find(answer[i])>6){
                            letter=answer[i];
                            word.append("\033[0;93m"+letter);
                        } else {
                            letter=answer[i];
                            word.append("\033[0;90m"+letter);
                        }
                        //can't change green to yellow
                        if (alphabet.substr(alphabet.find(letter)-3,3)!="32m"){
                            alphabet.insert(alphabet.find(letter), "\033[0;93m");
                        } 
                        //triples
                    } else if (gTriple.find(answer[i])<6){
                        
                        //if only in answer once
                        if (doubles.find(answer[i])>6){
                            eGuess=guess;
                            eGuess.replace(guess.find(answer[i]),1,"1");
                            eGuess2=eGuess;
                            eGuess2.replace(eGuess.find(answer[i]),1,"2");
                            //if second location isn't green, third location isn't green, letter is in the word?, previous aren't green, previous aren't yellow
                            if (eGuess.find(answer[i])!=answer.find(answer[i])&&eGuess2.find(answer[i])!=answer.find(answer[i])&&guess.find(answer[i])<6&&green.find(answer[i])>6&&yellowed.find(answer[i])>6){
                                letter=answer[i];
                                word.append("\033[0;93m"+letter);
                                yellowed.append(letter);
                            } else {
                                letter=answer[i];
                                word.append("\033[0;90m"+letter);
                            }
                            if (alphabet.substr(alphabet.find(letter)-3,3)!="32m"){
                                alphabet.insert(alphabet.find(letter), "\033[0;93m");
                            }
                            //if in answer twice
                        } else {
                            eGuess=guess;
                            eGuess.replace(guess.find(answer[i]),1,"1");
                            eGuess2=eGuess;
                            eGuess2.replace(eGuess.find(answer[i]),1,"2");
                            eAnswer=answer;
                            eAnswer.replace(answer.find(answer[i]),1,"1");
                            //if second location isn't green OR third location isn't green, letter is in the word?, 
                            if ((eGuess.find(answer[i])!=answer.find(answer[i])||eGuess2.find(answer[i])!=eAnswer.find(answer[i]))&&guess.find(answer[i])<6){
                                //both others are green
                                if (eGuess.find(answer[i])==answer.find(answer[i])&&eGuess2.find(answer[i])==answer.find(answer[i])){
                                    letter=answer[i];
                                    word.append("\033[0;98m"+letter);
                                    //one is green
                                    //if second is green or third is green and no yellows
                                } else if ((eGuess.find(answer[i])==answer.find(answer[i])||eGuess2.find(answer[i])==answer.find(answer[i]))&&yellowed.find(answer[i])>6){
                                    letter=answer[i];
                                    word.append("\033[0;93m"+letter);
                                    yellowed.append(letter);
                                    //neither green
                                    //if  2 yellows or 1 yellow and 1 green (dark)
                                } else if (count(yellowed.begin(), yellowed.end(), answer[i])==2||(count(yellowed.begin(), yellowed.end(), answer[i])==1&&green.find(answer[i])<6)){
                                    letter=answer[i];
                                    word.append("\033[0;90m"+letter);
                                    yellowed.append(letter);
                                    //if no yellows yet, not 2 greens OR 1 yellow, 0 greens
                                } else if ((yellowed.find(answer[i])>6&&count(green.begin(),green.end(), answer[i])!=2)||(count(yellowed.begin(), yellowed.end(), answer[i])==1&&count(green.begin(),green.end(), answer[i])==0)){
                                    letter=answer[i];
                                    word.append("\033[0;93m"+letter);
                                    yellowed.append(letter);
                                } else {
                                    letter=answer[i];
                                    word.append("\033[0;90m"+letter);
                                }
                               
                            //gray letters
                            } else {
                                letter=answer[i];
                                word.append("\033[0;90m"+letter);
                            }
                            if (alphabet.substr(alphabet.find(letter)-3,3)!="32m"){
                                alphabet.insert(alphabet.find(letter), "\033[0;93m");
                            }
                        }
                    }
                    yellow=true;
                } 
            }
            //showing wrong
            if (guess[j]!=answer[j]&&!yellow){
                letter=guess[j]; 
                word.append("\033[0;90m"+letter);
                if (alphabet.substr(alphabet.find(letter)-3,3)!="93m"&&alphabet.substr(alphabet.find(letter)-3,3)!="32m"){
                    alphabet.insert(alphabet.find(letter), "\033[0;90m");
                }
            }
        }
    }
    
    return greens;
}

//showing them how to play if they want
void instructions(int greens, string alphabet, string word, int &won){
    //c++ is annoying
    vector <string> trial;
    cout<<"\nIn this game you try to guess a 5 letter word, but you ony have 6 tries.";
    cout<<"\nEvery guess must be an actual English word.";
    cout<<"After you guess the letter will change colours.";
    cout<<"\033[0;32m\nGreen means that the letter is in the right space.";
    cout<<"\033[0;93m\nYellow means the letter is in the word but not in that spot.";
    cout<<"\033[0;90m\nBlack/gray means that the letter is not in any word.";
    cout<<"\nThese colours show up on both the words itself and on the alphabet on the bottom.";
    cout<<"\nHere is an example of a finished game: ";

    //checking and showing right/wrong
    greens=inWord("HAPPY", "TRADE", alphabet, word, won, 0, trial, "", "", "", "");
    greens=inWord("BLACK", "TRADE", alphabet, word, won, 0, trial, "", "", "", "");
    greens=inWord("STARE", "TRADE", alphabet, word, won, 0, trial, "", "", "", "");
    greens=inWord("TRACE", "TRADE", alphabet, word, won, 0, trial, "", "", "", "");
    greens=inWord("TRADE", "TRADE", alphabet, word, won, 0, trial, "", "", "", "");
    cout<<word<<endl;
    //alphabet
    cout<<alphabet;

    //continuing
    cout<<"\n\033[0;1mPlease enter anything to continue: ";
    cin>>word;
    system("clear");
}

//multi-wordle
void instructions2(string word){
    cout<<"\nA multi wordle game is a game where you play muiple games of wordle at once. \nYou guess the same word for all wordles, but the answers are all different.";
    cout<<"\nThe games are vertical but you can answer them in any order.";
    cout<<"\nDoesn't matter how many games you play you will get five more guesses than words.";

    //continuing
    cout<<"\n\033[0;1mPlease enter anything to continue: ";
    cin>>word;
    system("clear");
}

//main function
int main(){
    //variables
    int guesses=0, greens=0, endCount=0, avg=0, gameNum=0, wins=0, streak=0, maxStreak=0, won=0, numWordles, inCompleted=0, funFound=0, funTotal;
    bool discovered=false, found=false;
    string guess, answer1="0", answer2="0", answer3="0", answer4="0", playAgain, word, intro, word1, word2, word3, word4;
    string letters="QWERTYUIOPASDFGHJKLZXCVBNM";
    string alphabet="\033[100;97mQ\033[100;97mW\033[100;97mE\033[100;97mR\033[100;97mT\033[100;97mY\033[100;97mU\033[100;97mI\033[100;97mO\033[100;97mP\033[1;0m\n \033[100;97mA\033[100;97mS\033[100;97mD\033[100;97mF\033[100;97mG\033[100;97mH\033[100;97mJ\033[100;97mK\033[100;97mL\033[1;0m\n  \033[100;97mZ\033[100;97mX\033[100;97mC\033[100;97mV\033[100;97mB\033[100;97mN\033[100;97mM\033[1;0m";
    // Load all words into set
    set <string> wordleWords = getWordleWords();
    set <string> wordleAnswers = getWordleAnswers();
    //the guess and answers
    vector <string> doublesA;
    vector <string> triplesA;
    vector <string> doublesG;
    vector <string> triplesG;
    vector <string> words;
    vector <string> answers;
    vector <string> alphabets;
    vector <string> wordsFound;
    vector <string> completed;

    //getting random
    srand(time(0));


    //asking to play
    cout<<"Welcome to wordle.";
    cout<<"\nTo get instructions on how to play, click 'i', otherwise enter 'n': ";
    cin>>intro;
    //going to instructions
    if (intro=="i"||intro=="I"){
        instructions(greens, alphabet, word, won);
    }
    cout<<"Do you need instructions on what a multi wordle-wordle is? (i/n): ";
    cin>>intro;
    //going to multi-wordle instructions
    if (intro=="i"||intro=="I"){
        instructions2(word);
    }
    cout<<"\n\nPlease enter how many wordles you want to play. \nIt can be any number but having a number larger than 20 will be annoying to look at:  ";
    cin>>numWordles;
    while (numWordles<1){
        cout<<"\n\nPlease enter how many wordles you want to play. \nIt can be any number \033[0;91mgreater than 0 \033[0;1mbut having a number larger than 20 will be annoying to look at:  ";
        cin>>numWordles;
    }
    

    //setting answer
    for (int i=0; i<numWordles; i++){
        answers.push_back(randomWord(wordleAnswers));
        words.push_back("");
        doublesA.push_back("");
        triplesA.push_back("");
        doublesG.push_back("");
        triplesG.push_back("");
        alphabets.push_back(alphabet);
        hasMultiple(answers[i], doublesA[i], triplesA[i]);
    }

    system("clear");

    //loop to play multiple times
    do{
        //showing keyboard
        cout<<"\n";
        cout<< alphabet;
        
        //loop for guesses
        for (int guessNum=1; guessNum<=numWordles+5; guessNum++) {
            //asking for the guess
            do{
                cout<<"\033[0;1m\nGuess number "<<guessNum<<": ";
                cin>>guess;
                system("clear");
                capitalize(guess);
                funWords(guess, discovered, funFound, wordsFound, funTotal, guessNum);
                if (!isWord(guess, letters, wordleWords)){
                    //words and alphabet
                    for (int i=0; i<numWordles; i++){
                        cout<<"\n"<<words[i]<<endl;
                        cout<<"\n"<<alphabets[i];
                    }
                    if (guess=="ANSWERS"){
                        cout<<"\nAnswers: ";
                        for (int i=0; i<numWordles; i++){
                            cout<<"\n"<<answers[i];
                        }
                    }
                    //telling incorrect
                    cout<<"\nNot a word. Please try again: ";
                }
            } while (!isWord(guess, letters, wordleWords));

            //checking and showing right/wrong
            for (int i=0; i<numWordles; i++){
                hasMultiple(guess, doublesG[i], triplesG[i]);
                if (numWordles!=completed.size()){
                    greens=inWord(guess, answers[i], alphabets[i], words[i], won, i, completed, doublesA[i], triplesA[i], doublesG[i], triplesG[i]);
                }
                inCompleted=0;
                cout<<"\n"<<words[i]<<endl;

                //outputting alphabet
                cout<<"\n";
                cout<<alphabets[i];
            }

            //exiting if right
            if (completed.size()==numWordles){
                endCount=guessNum;
                guessNum=7000;
            }
        }
        //showing results
        if (completed.size()==numWordles){
            printf("\n\033[0;94mYou got the answers in only %i guesses!", endCount);
            cout<<"\nGood job";
            wins+=1;
            streak+=1;
            avg+=endCount;
            if (streak>maxStreak){
                maxStreak=streak;
            }
        } else {
            cout<<"\n\033[0;91mToo bad :( \nThe answers were ";
            for (int i=0; i<numWordles; i++){
                found=false;
                if (numWordles!=completed.size()){
                    greens=inWord(guess, answers[i], alphabets[i], words[i], won, i, completed, doublesA[i], triplesA[i], doublesG[i], triplesG[i]);
                }

                //showing which are right and which are wrong
                for (int j=0; j<completed.size(); j++){
                    if (answers[i]==completed[j]){
                        cout<<"\033[0;32m";
                        found=true;
                    } else if (!found){
                        cout<<"\033[0;91m";
                    }
                }
                cout<<answers[i]<<", ";
            }
            cout<<"\n\033[0;94mYou'll get it next time";
            avg+=7;
            streak=0;
        }
        cout<<"\nYour current streak is "<<streak;
        cout<<"\nYour max streak is "<<maxStreak;

        //fun
        if (discovered==true){
            cout<<"\nBy now you have discovered ";
            for (int i=0; i<wordsFound.size(); i++){
                cout<<wordsFound[i]<<", ";
            }
            if (funTotal-funFound==0){
                cout<<"\nThat is all the bonus words! \nGreat job!";
            } else {
                cout<<"\nThere are still "<<funTotal-funFound<<" words left to find. \nKeep going!";
            }
        }

        //adding to the num of games
        gameNum+=1;

        //playing again
        usleep(5000000);
        cout<<"\n\n\033[0;1mDo you want to play again? ";
        cin>>playAgain;
        
        //resetting stuff 
        word=" ";
        //alphabet={"Q" , "W" , "E" , "R" , "T" , "Y" , "U" , "I" , "O" , "P" , "A" , "S" , "D" , "F" , "G" , "H" , "J" , "K" , "L" , "Z" , "X" , "C" , "V" , "B" , "N" , "M"};
        words.clear();
        completed.clear();
        alphabets.clear();
        answers.clear();
        for (int i=0; i<numWordles; i++){
            answers.push_back(randomWord(wordleAnswers));
            words.push_back("");
            doublesA.push_back("");
            triplesA.push_back("");
            doublesG.push_back("");
            triplesG.push_back("");
            alphabets.push_back(alphabet);
            hasMultiple(answers[i], doublesA[i], triplesA[i]);
        }
        system("clear");

    } while (playAgain=="yes"||tolower(playAgain[0])==121);
    //final results
    printf("\n\nYou have played %i games. \nYou won %i games, with an average of %.2f guesses per game. \nGood job!\n\n\n_", gameNum, wins, float(avg)/float(gameNum));
    printf("\nYou currenty have streak of %i, with a max streak of %i. ", streak, maxStreak);
}