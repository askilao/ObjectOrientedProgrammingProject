#include "../include/ListTool2B.h"
#include "../include/constenum.h"
#include "../include/utilities.h"
#include "../include/Nations.h"
#include "../include/Competitors.h"
#include "../include/Competitions.h"
#include "../include/Competition.h"
#include "../include/Medals.h"
#include "../include/Points.h"
#include "../include/global.h"
#include <iostream>
#include <locale> //isdigit

using namespace std;

//Function declarations
void mainMenu();
void nationMenu();
void competitorMenu();
void eventMenu();
void startMenu();
void resultMenu();

//Global variables
Nations nationbase;
Competitors compbase;
Competitions cbase;
Medals medalbase;
Points pointbase;
extern int lastID;      //NUMBER OF LAST EVENT REGISTERED


int main() {   
	    mainMenu();
}

void mainMenu() {

    char ch;
    char buffer[STRLEN];

    nationbase.read();
    compbase.read();
   cbase.read();

    cout << MAINMENU << endl;

    ch = toupper(getInput("> ", buffer));
    while (ch != 'X') {
        switch (ch) {
        case 'N': nationMenu(); break;
        case 'D': competitorMenu(); break;
        case 'G': eventMenu(); break;
        case 'O': cbase.eventMenu(); break;
        case 'M': medalbase.displayMedals(); break;
        case 'P': pointbase.displayPoints(); break;
        default: cout << "Bad input\a" << endl; break;
        }
        cout << MAINMENU << endl;

        ch = toupper(getInput("> ", buffer));
    }

    nationbase.write();
    compbase.write();
    cbase.write();

}



void nationMenu() {
    char ch;
    char buffer[STRLEN];

    
        cout << "\n\t\tNation Menu:"
            << "\n\tN- Register Nation"
            << "\n\tE- Edit Nation"
            << "\n\tA- Print all Nation Main Data"
            << "\n\tT- Print all Nation Competitors"
            << "\n\tS- Print all Nation Data"
            << "\n\tQ- Return to Main Menu" << endl;

            ch = toupper(getInput("> ", buffer));
        while (ch != 'Q') {         
            switch (ch) {
            case 'N': nationbase.registerNation(); break;
            case 'E': nationbase.editNation(); break;
            case 'A': nationbase.limitedDisplay(); break;
            case 'T': nationbase.displaySquad(); break;
            case 'S': nationbase.display(); break;
            default: cout << "bad input" << endl;
                break;
            }
            
            ch = toupper(getInput("> ", buffer));
        }
    }


void competitorMenu() {
    char ch;
    char buffer[STRLEN];
    
    cout << "\n\t\tCompetitor Menu:"
        << "\n\tN- Register new Competitor"
        << "\n\tE- Edit Competitor"
        << "\n\tA- Print all Competitor Main Data"
        << "\n\tS- Print all Competitor Data"
        << "\n\tQ- Return to Main Menu" << endl;

         ch = toupper(getInput("> ", buffer));
    while (ch != 'Q') {
        switch (ch) {
        case 'N': compbase.registerCompetitor(); break;
        case 'E': compbase.editCompetitor(); break;
        case 'A': compbase.displayAllCompetitors(); break;
        case 'S': compbase.displayElement(); break;
        case 'Q': mainMenu(); break;
        default: cout << "bad input" << endl;
            break;
        }
         ch = toupper(getInput("> ", buffer));
    }
}

void eventMenu() {
    char ch;
    char buffer[STRLEN];

    cout << "\n\tCompetition Menu:"
        << "\n\tN- Register new Competition"
        << "\n\tE- Edit Competition"
        << "\n\tA- Print all Competition Main Data"
        << "\n\tS- Print all Competition Data"
        << "\n\tQ- Return to Main Menu" << endl;

        ch = toupper(getInput("> ", buffer));
    while (ch != 'Q') {
        switch (ch) {
        case 'N': cbase.addCompetition(); break;
        case 'E': cbase.editCompetition(); break;
        case 'A': cbase.limitedDisplay(); break;
        case 'S': cbase.displayCompetition(); break;
        case 'Q': mainMenu(); break;
        default: cout << "bad input" << endl;
            break;
        }
        ch = toupper(getInput("> ", buffer));
    }
}



void startMenu() {
    char ch;
    char buffer[STRLEN];

    cout << "\n\t Starter Menu:"
        << "\n\tS- Print Starter List "
        << "\n\tN- New Starter List"
        << "\n\tE- Edit Starter List"
        << "\n\tF- Remove Starter List and Local Data"
        << "\n\tQ- Return to Main Menu" << endl;

        ch = toupper(getInput("> ", buffer));
    while (ch != 'Q') {
        switch (ch) {
        case 'S':  break;
        case 'N':  break;
        case 'E':  break;
        case 'F':  break;
        case 'Q': mainMenu(); break;
        default: cout << "bad input" << endl;
            break;
        }
        ch = toupper(getInput("> ", buffer));
    }
}

void resultMenu() {
    char ch;
    char buffer[STRLEN];

    cout << "\n\tResult Menu:"
        << "\n\tS- Print Results"
        << "\n\tN- New Result List"
        << "\n\tF- Remove Result List and Local Data"
        << "\n\tQ- Return to Main Menu" << endl;

        ch = toupper(getInput("> ", buffer));
    while (ch != 'Q') {
        switch (ch) {
        case 'S':  break;
        case 'N':  break;
        case 'F':  break;
        case 'Q': mainMenu(); break;
        default: cout << "bad input" << endl;
            break;
        }
        ch = toupper(getInput("> ", buffer));
    }
}

