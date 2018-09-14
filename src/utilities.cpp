#include "../include/utilities.h"
#include "../include/constenum.h"
#include <cstring>
#include <iostream>
using namespace std;


///////////////////////INPUT FUNCTIONS///////////////////////////
char getInput(char t[], char s[]) {
    cout << '\n' << t;
    cin.getline(s, STRLEN);
    while (strlen(s) > 1 || numCheck(s)) {
        cout << "Bad input\a" << endl;
        cout << '\n' << t;	cin.getline(s, STRLEN);
    }
    return s[0];

}
void getInput(char t[], char s[], const int LEN) {
    do {
        cout << '\n' << t << " (Max " << LEN << " characters!) " << endl;
        cout << "\t> "; cin.getline(s, STRLEN);
        for (int i = 0; i < strlen(s); i++)
            s[i] = toupper(s[i]);
        if (strlen(s) > LEN)
            cout << "\nBad input\a" << endl;

    } while (strlen(s) > LEN);
}
void getIOC(char t[], char s[], const int LEN) {
    do {
        cout << '\n' << t << "  ( " << LEN -1 << " characters!) " << endl;
        cout << "\t> "; cin.getline(s, STRLEN);

        if (strlen(s) !=LEN-1) //rett st�rrelse p� IOC
            cout << "\nBad input\a" << endl;

    } while (numCheck(s) || strlen(s) !=LEN-1);

	for (int i = 0; i < strlen(s); i++)
		s[i] = toupper(s[i]);
}

int getInput(char t[], char s[], int MIN, int MAX) {
    int n = 0;

    do {
        cout << '\n' << t << " (" << MIN << " - " << MAX << " ): ";
        cin.getline(s, STRLEN);

        if (numCheck(s))
            n = atoi(s);
        if (!numCheck(s) || n<MIN || n>MAX)
            cout << "\nBad input\a" << endl;
    } while (!numCheck(s) || n < MIN || n > MAX);

    return n;
}

bool numCheck(char s[]) { //checks if an array is a number
    for (int i = 0; i < strlen(s); i++)
        return isdigit(s[i]) ? true : false;
}

/////////////////////DISPLAY FUNCTIONS//////////////////////////

void displayDate(int day, int month, int year, int hour, int min) {


    cout << "Time and date: ";
    if (day < 10) cout << 0;
    cout << day << "/";
    if (month < 10) cout << 0;
    cout << month << "-";
    cout << year;
    cout << "  ";
    if (hour < 10) cout << 0;
    cout << hour << ":";
    if (min < 10) cout << 0;
    cout << min;
}
