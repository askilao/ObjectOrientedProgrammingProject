#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "../include/Competitions.h"
#include "../include/ListTool2B.h"
#include "../include/constenum.h"
#include "../include/Competition.h"
#include "../include/utilities.h"
#include <iostream>
#include <fstream>
using namespace std;

int lastID = 1000;	//	BASEnumber for generating uniqueID

Competitions::Competitions()	//	Constructor
{
	competitions = new List(Sorted);
}
Competitions::~Competitions()	//	Destructor
{
	delete competitions;
}

List * Competitions::returnList() {
    return competitions;
}

void Competitions::eventMenu() {
    char ch;
    char buffer[STRLEN];
    Competition* temp;
    if (!competitions->isEmpty()) {
        getInput("Enter competition name: ", buffer, STRLEN);
        competition_name = new char[strlen(buffer) + 1];  strcpy(competition_name, buffer);
        while (!competitions->inList(competition_name)) {
            cout << "Competition not found" << endl;
            getInput("Enter competition name: ", buffer, STRLEN);
            competition_name = new char[strlen(buffer) + 1];  strcpy(competition_name, buffer);
        }
        temp = (Competition*)competitions->remove(competition_name);
        competitions->add(temp);

        cout << "\n\tEvent Menu:"
            << "\n\tN- Register new Event"
            << "\n\tE- Edit Event"
            << "\n\tF- Remove Event and Local Data"
            << "\n\tA- Print all Event Data"
            << "\n\tL- Competitorlist"
            << "\n\tR- Results"
            << "\n\tQ- Return to Main Menu" << endl;

        ch = toupper(getInput("> ", buffer));
        while (ch != 'Q') {
            switch (ch) {
            case 'N':temp->registerEvent(); break;
            case 'E':temp->editEvent(); break;
            case 'F':temp->removeEvent();   break;
            case 'A':temp->displayEvent(); break;
            case 'L':temp->startMenu();   break;
            case 'R':temp->resultsMenu(); break;
            case 'Q':   break;
            default: cout << "bad input" << endl;
                break;
            }
            cout << "\n\tEvent Menu:"
                << "\n\tN- Register new Event"
                << "\n\tE- Edit Event"
                << "\n\tF- Remove Event and Local Data"
                << "\n\tA- Print all Event Data"
                << "\n\tL- Competitorlist"
                << "\n\tR- Results"
                << "\n\tQ- Return to Main Menu" << endl;
            ch = toupper(getInput("> ", buffer));
        }
    }
    else
        cout << "\nBefore adding an event, you'll need to create a competition." << endl;
}

void Competitions::display()	//	Display all elements in lists data
{
	Competition* tmp;
	int num_elements = competitions->noOfElements();
	for (int i = 1; i <= num_elements; i++) {
		tmp = (Competition*)competitions->removeNo(i);	//	Removes num i from list so it can be displayed.
		tmp->display();	//	Uses whatever tmp points to its display function.
		competitions->add(tmp);	//	Puts 'back' element after used
	}
}

void Competitions::addCompetition()
{
	char buff[MAX_LEN_COMPETITION_NAME];
	Competition* competition;

	getInput("Enter name of competition to add", buff, MAX_LEN_COMPETITION_NAME);

	if (!competitions->inList(buff)) {// Checks if already added
		competition = new Competition(buff);
		competitions->add(competition);

	} else cout << "Already in list";
}

void Competitions::editCompetition()
{
	Competition* temp;
	char buffer[MAX_LEN_COMPETITION_NAME];

	getInput("Enter existing competition name to edit", buffer, MAX_LEN_COMPETITION_NAME);
	competition_name = new char[strlen(buffer) + 1]; strcpy(competition_name, buffer);
	while (!competitions->inList(competition_name)) {
		cout << "Cant find competition by that name" << endl;
		getInput("Enter existing competition name to edit", buffer, MAX_LEN_COMPETITION_NAME);
		competition_name = new char[strlen(buffer) + 1]; strcpy(competition_name, buffer);
	}
	temp = (Competition*)competitions->remove(competition_name);
	temp->editName();
	competitions->add(temp);
}

void Competitions::limitedDisplay()
{

		Competition* temp;
		int nr = competitions->noOfElements();
		if (competitions->noOfElements() != 0) {
			for (int i = 1; i <= nr; i++) {

				temp = (Competition*)competitions->removeNo(i); //tar ut en nation og displayer den
				competitions->add(temp);
				temp->limitedDisplay();
			}
		}
		else
			cout << "No competitons registrated" << endl;
}

void Competitions::displayCompetition() {
    char buffer[STRLEN];
    char* s;
	getInput("Enter the name of competition you want data shown", buffer, STRLEN);
    s = new char[strlen(buffer) + 1];  strcpy(s, buffer);
	if (!competitions->inList(s)) {
		cout << "Cant find competition";
	} else 	competitions->displayElement(s);
}

void Competitions::read() {
	Competition* temp;
	char buffer[MAX_LEN_COMPETITION_NAME];
	int nr = 0;

	ifstream iFile("GRENER.DTA");
    if (iFile) {
        cout << "Reading from GRENER.DTA....." << endl;
        iFile >> nr; iFile.ignore();
		iFile >> lastID; iFile.ignore();
            if (nr != 0) {
                for (int i = 1; i <= nr; i++) {
                    iFile.getline(buffer, MAX_LEN_COMPETITION_NAME);
                    competition_name = new char[strlen(buffer) + 1];  strcpy(competition_name, buffer);
                    if (!competitions->inList(competition_name)) {
                        temp = new Competition(competition_name, iFile);
                        competitions->add(temp);
                    }
                }
            }
        }

        else
            cout << "No file named GRENER.DTA..." << endl;
}

void Competitions::write() {
	Competition* temp;
	int nr = competitions->noOfElements();
	ofstream oFile("GRENER.DTA");
	oFile << nr << endl;
	oFile << lastID << endl;
        cout << "Writing to GRENER.DTA" << endl;
        for (int i = 1; i <= nr; i++) {
            temp = (Competition*)competitions->removeNo(i);
            temp->write(oFile);
            competitions->add(temp);
        }
}
