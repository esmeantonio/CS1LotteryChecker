/*
 Esmeralda Antonio
 CS 1, Section #100
 Assignment #5, Problem #1
 Lottery Checker
A program that will allow a user to select their lotto numbers, randomly generate the winning
lotto numbers for the week, and then checks the winning numbers against the user's numbers to
see how many numbers the user guessed correctly.
 */

 

#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <cstdlib>
using namespace std;

//Global Constant -> Array size for user's loto numbers and winning numbers
int LottoArraySize = 7;

//Prototypes
void getLottoPicks(int userInput[], int arraySize);
int checkDuplicates(int userInput[], int arraySize, int input);
void GenWinNums(int userInput[], int arraySize);
int countOccurence(int value, int lottoNumbers[]);
void checkTicket(int userInput[], int lottoNumbers[], string name);

int main() {
    int UserTicket[] {0, -1, 0, -1, 0, -1, 0};
    int WinningNums[] {0, -1, 0, -1, 0, -1, 0};
    char userChoice;
    string userName;
    
    do {
        cout << endl;
        cout << "LITTLETON CITY LOTTO MODEL:" << endl;
        cout << "---------------------------" << endl;
        cout << "1) Play Lotto" << endl;
        cout << "q) Quit Program" << endl;
        cout << "Please make a selection: ";
        cin >> userChoice;
        if (isdigit(userChoice)) {
            int choice2 = userChoice - '0';
            if (choice2 == 1){
                cout << "Please enter your name: " << endl;
                cin >> userName;
                UserTicket[0] = -1;
                getLottoPicks(UserTicket, LottoArraySize);
                cout << endl;
                GenWinNums(WinningNums, LottoArraySize);
                checkTicket(UserTicket, WinningNums, userName);
                //exit(1);
            } else {
                cout << "Invalid input. Please try again." << endl;
            }
        } else if (userChoice == 'q') {
            cout << "Thank you for playing." << endl;
            exit(2);
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    } while(true);
    return 0;
}



/*
getLottoPicks: asks user to enter their 7 lotto #'s for the week,
each user input should be stored in UserTicket
*/
void getLottoPicks(int userInput[], int arraySize) {
    int x = 0;
    //userInput[0] = -1;
    int input;
    do {
        cout << "Please enter number " << (x + 1) << ":";
        cin >> input;
        if (checkDuplicates(userInput, arraySize, input) == 0) {
            if (input >= 1 && input <= 40){
                userInput[x] = input;
                x++;
            } else {
                cout << "The number must be between 1 and 40." << endl;
            }
        } else if ((checkDuplicates(userInput, arraySize, input) > 0)) {
            cout << "No duplicate numbers are accepted." << endl;
            //exit(2);
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    } while(x < 7);
}



/*
NoDuplicates: checks for duplicate entries in an array
*/
int checkDuplicates (int userInput[], int arraySize, int input) {
    int count = 0;
    for (int i = 0; i < arraySize; i++) {
        if (userInput[i] == input) {
            count ++;
        }
    }
    return count;
}



/*
GenWinNums: randomly generate winning #'s, stored in WinningNums
*/
void GenWinNums(int userInput[], int arraySize) {
    srand((unsigned) time(NULL));
    int random = 1 + (rand() % 40);
    int x = 0;
    do {
        if (checkDuplicates(userInput, arraySize, random) == 0) {
            userInput[x] = random;
            x++;
        } else {
            random = 1 + (rand() % 40);
        }
    } while(x < arraySize);
}



/*
 countOccurence: Checks to see if the VALUE in user's
 ticket is a winning number
 */
int countOccurence(int value, int lottoNumbers[]) {
    int count = 0;
    for (int i = 0; i < LottoArraySize; i++) {
        if (value == lottoNumbers[i]) {
            count++;
        }
    }
    return count;
}



/*
 Compares user ticket to winning numbers, finds # of matches,
 prints results and winnings
 */
void checkTicket(int userInput[], int lottoNumbers[], string name) {
    int numberOfMatches = 0;
    
    for (int i = 0; i < name.length(); i++) {
        name[i] = toupper(name[i]);
    }
    cout << name << "'s LOTTO RESULTS" << endl;
    for (int j = 0; j < name.length(); j++) {
        cout << "-";
    }
    cout << "----------------" << endl;
    cout << "WINNING TICKET NUMBERS: ";
    for (int k = 0; k < LottoArraySize; k++) {
        if (lottoNumbers[k] >= 10) {
            cout << setw(2) << right << lottoNumbers[k] << "  ";
        } else {
            cout << setw(1) << right << lottoNumbers[k] << "  ";
        }
    }
    cout << endl;
    cout << setw(13) << right << name << "'s TICKET: ";
    for (int l = 0; l < LottoArraySize; l++) {
        if ((userInput[l] >= 10 && lottoNumbers[l] >= 10) || (userInput[l] < 10 && lottoNumbers[l] >= 10)) {
            cout << setw(2) << right << userInput[l] << "  ";
        } else if ((userInput[l] >= 10 && lottoNumbers[l] < 10)) {
            cout << setw(1) << left << userInput[l] << "  ";
        } else {
            cout << setw(1) << right << userInput[l] << "  ";
        }
    }
    cout << endl;
    
    //Checks for how many #'s user matched
    for (int i = 0; i < LottoArraySize; i++) {
        if (countOccurence(userInput[i], lottoNumbers) > 0) {
            numberOfMatches++;
        }
    }
    
    //Displays results
    cout << "RESULTS:" << endl;
    cout << "--------" << endl;
    cout << "Number Matches: ";
    if (numberOfMatches <= 2) {
        cout << numberOfMatches << endl;
        cout << "Winnings      : SORRY NOTHING" << endl;
    } else if (numberOfMatches == 3) {
        cout << numberOfMatches << endl;
        cout << "Winnings      : FREE TICKET" << endl;
    } else if (numberOfMatches == 4) {
        cout << numberOfMatches << endl;
        cout << "Winnings      : NOT BAD";
    } else if (numberOfMatches == 5) {
        cout << numberOfMatches << endl;
        cout << "Winnings      : LUCKY YOU! - $5,000";
    } else if (numberOfMatches == 6) {
        cout << numberOfMatches << endl;
        cout << "Winnings      : GREAT! - $100,000";
    } else {
        cout << numberOfMatches << endl;
        cout << "Winnings      : JACKPOT!!! - $1 MILLION";
    }
    cout << endl;
}
