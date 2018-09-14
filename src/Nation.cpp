#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "../include/Nation.h"
#include "../include/Competitors.h"
#include "../include/ListTool2B.h"
#include "../include/constenum.h"
#include "../include/utilities.h"
#include "../include/global.h"
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;


Nation::Nation() {
    cout << "This should never be called" << endl;
}

Nation::~Nation() {
    delete[] longname;
    delete[] contactname;
}

// Adds paramter as the new nation
Nation::Nation(char* s) : TextElement(s) {
    char buffer[STRLEN];
    competitorIDlist = new List(Sorted);
	// Reads its data members
    getInput("Enter Full Name: ", buffer, STRLEN);
    longname = new char[strlen(buffer) + 1];  strcpy(longname, buffer);
    getInput("Enter Contactname: ", buffer, STRLEN);
    contactname = new char[strlen(buffer) + 1];  strcpy(contactname, buffer);
    contactphone = getInput("Contactphone: ", buffer, MINPHONE, MAXPHONE);
    squadsize = getInput("Number of competitors: ", buffer, 1, MAXCOMPETITORS);

}
// Adds s nation read from file as the new nation
Nation::Nation(char * s, ifstream & in) : TextElement(s) {
    char buffer[STRLEN];
    competitorIDlist = new List(Sorted);
	// Sets data members as saved on file
    in.getline(buffer, STRLEN);
    longname = new char[strlen(buffer) + 1];  strcpy(longname, buffer);
    in.getline(buffer, STRLEN);
    contactname = new char[strlen(buffer) + 1];  strcpy(contactname, buffer);
    in >> contactphone; in.ignore();
    in >> squadsize; in.ignore();
}

char * Nation::returnName(){
    return text;
}
//	Edits the data the user chooses, Full name, Contact name or Phone number
void Nation::editNation() {
    char buffer[STRLEN];
    char ch;
    cout << "\n\tEdit: "
        << "\nF- Full name"
        << "\nC- Contact name"
        << "\nP- ContactPhone" << endl;
     ch = toupper(getInput("> ", buffer));

    switch (ch) {
    case 'F':   getInput("Enter Full Name: ", buffer, STRLEN);
                delete[] longname;
                longname = new char[strlen(buffer) + 1];  strcpy(longname, buffer); break;
    case 'C':   getInput("Enter Contactname: ", buffer, STRLEN);
                delete[] contactname;
                contactname = new char[strlen(buffer) + 1];  strcpy(contactname, buffer); break;
    case 'P':   contactphone = getInput("Contactphone: ", buffer, MINPHONE, MAXPHONE); break;
    default: cout << "Bad input" << endl;
        break;
    }

}
//	Displays IOC, Name, Contact name and phone number and its competitors
void Nation::display() {
    NumElement* temp;
    Competitor* compTemp;
    int compID = 0;
    int nr = competitorIDlist->noOfElements();
    cout << "-----------------------" << endl;
    cout << "IOC code: " << text << endl;
    cout << "Full name: " << longname << endl;
    cout << "Contact name: " << contactname << endl;
    cout << "Contact phone: " << contactphone << endl;
    cout << "Number of competitors: " << squadsize << endl;
	
    if (competitorIDlist->noOfElements() != 0) { // If any competitor they are displayed
        cout << "Competitors:" << endl;
        for (int i = 0; i <=nr; i++) {
            if (competitorIDlist->inList(i)) {
                temp = (NumElement*)competitorIDlist->remove(i);
                compID = temp->getNumber();
                competitorIDlist->add(temp);
                compTemp = compbase.getCompetitor(compID);
                compTemp->display();
                cout << "///////////////////////" << endl;
                cout << endl;
            }
        }
    }
}
// Displays IOC, Name and number of competitors
void Nation::limitedDisplay() {
    cout << "-----------------------" << endl;
    cout << "IOC code: " << text << endl;
    cout << "Full name: " << longname << endl;
    cout << "Number of competitors: " << squadsize << endl;
    cout << totalcompetitors << endl;
}

// Prints a Nations squad
void Nation::displaySquad() {
    NumElement* temp;
    Competitor* compTemp;
    int compID = 0;
    cout << "Competitors:" << endl;
    for (int i = 0; i < MAXCOMPETITORS; i++) {
        if (competitorIDlist->inList(i)) {
            temp = (NumElement*)competitorIDlist->remove(i);
            compID = temp->getNumber();
            competitorIDlist->add(temp);
            compTemp = compbase.getCompetitor(compID);
            compTemp->display();
            cout << "///////////////////////" << endl;
        }

    }
}

void Nation::addCompetitor(int n) {
    competitorIDlist->add(new NumElement(n));
    totalcompetitors++;	//	To help keep track
}
// Writes data to file
void Nation::write(ofstream &  out) {
    int compID = 0;
    int nr = competitorIDlist->noOfElements();

    out << text << endl;
    out << longname << endl;
    out << contactname << endl;
    out << contactphone << endl;
    out << squadsize << endl;

}
// Returns true if there is space for more competitors in squad given its nation
bool Nation::totalSquad() {	
    if (totalcompetitors < squadsize)
        return true;
    else
        return false;
}


