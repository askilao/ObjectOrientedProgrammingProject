#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "../include/Competitors.h"
#include "../include/ListTool2B.h"
#include "../include/Competitor.h"
#include "../include/constenum.h"
#include "../include/utilities.h"
#include "../include/global.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

extern Nations nationbase;

Competitors::Competitors() {
    competitorlist = new List(Sorted);
}

Competitors::~Competitors() {
    delete competitorlist;
}

List * Competitors::returnList(){
    return competitorlist;
}

//if the input ID is not already in use, this function will create a temporary object
//and put it in the competitorlist. If ID is already in use, it'll reply exactly that.
//TODO needs to add the check functions to prevent adding more competitors to a nation than registered in the first place
// look at g
void Competitors::registerCompetitor() {
	char buffer[MAXCOMPETITORS];
	Competitor* comptemp;
    char* temp;
    //int squadsize;

    if (nationbase.emptyNation()) {

        getIOC("Enter Nation: ", buffer, IOCLEN);
        temp = new char[strlen(buffer) + 1];  strcpy(temp, buffer);
        while (!nationbase.checkNation(temp)) {
            cout << "That nation is not registered" << endl;
            getIOC("Enter Nation: ", buffer, IOCLEN);
            temp = new char[strlen(buffer) + 1];  strcpy(temp, buffer);
        }

        if (nationbase.nationSquadSize(temp)) { //sjekker om det er plass til en ny deltager under den spesifikke nasjonen
            id = getInput("ID number: ", buffer, 1, MAXCOMPETITORS);

            if (!competitorlist->inList(id)) {
                comptemp = new Competitor(temp, id);
                competitorlist->add(comptemp);
                compbase.write();
            }
            else
                cout << "\nThis competitor is already registered" << endl;
        }
        else
            cout << "No more room for competitors" << endl;
    }
           else 
               cout << "\nBefore adding a competitor, you need to register a nation." << endl;           	
}

//lets you edit a competitors data
void Competitors::editCompetitor() {
    char buffer[MAXCOMPETITORS];
    Competitor* temp;

   
    id = getInput("ID number: ", buffer, 1, MAXCOMPETITORS);
    while (!competitorlist->inList(id)) {
        cout << "No competitor with this ID in list" << endl;
        id = getInput("ID number: ", buffer, 1, MAXCOMPETITORS);
    }
    if (!(NULL)) {
        temp = (Competitor*)competitorlist->remove(id);
        temp->editCompetitor();
        competitorlist->add(temp);
        compbase.write();
    }

}

//simply displays all competitors with their own data.
void Competitors::displayAllCompetitors() {
    if (!competitorlist->isEmpty()) {
        cout << "\nCompetitors: " << endl;
        competitorlist->displayList();
    }
    else cout << "\nNo competitors in list. Please add before display." << endl;
}

//user is asked whether to find a competitor by searching ID or name,
//then either types a respective ID or name. If not found in list, program 
//will reply. 
//Case 'I' removes the object from the list, placing it in a temporary object,
//then displays this.
//Case 'N' compares a text with an additional checkName function; if the input name 
//matches the stored name in a list object, it'll display.
void Competitors::displayElement() {
    char buffer[STRLEN];
    char ch;
    cout << "\n\tSearch by ID or name: "
         << "\nI- ID-number"
         << "\nN- Name" << endl;
    ch = toupper(getInput("> ", buffer));

    switch (ch) {
    case 'I': {
        int nr;
        nr = getInput("ID number: ", buffer, 1, MAXCOMPETITORS);
        Competitor* temp = (Competitor*)competitorlist->remove(nr);
        if (temp != nullptr) {
            competitorlist->add(temp);
            temp->display();
        }
        else {
            cout << "\nNo competitor with this ID" << endl;
        }
        
        
    } break;
    case 'N': { 
        int nr = competitorlist->noOfElements();
        int compID = 0;
        Competitor* temp;
        

        getInput("Enter Full Name: ", buffer, STRLEN);
        char* s = new char[strlen(buffer) + 1];  strcpy(s, buffer);
        for (int i = 0; i <= nr; i++) {
            temp = (Competitor*)competitorlist->removeNo(i);
            competitorlist->add(temp);
            if (temp->checkName(s) != 0)
                compID = temp->checkName(s);
        }
        temp = (Competitor*)competitorlist->remove(compID);
        if (temp != nullptr) {
            competitorlist->add(temp);
            temp->display();
        }
        else
            cout << "\nCouldn't find competitor by this name. Sure you"
                    " typed correctly? " << endl;
        
    } break;
    default: break;
    }
}

//takes a competitors id, uses display-function to display competitor data
void Competitors::displayElement(int id) {
    Competitor* temp = (Competitor*)competitorlist->remove(id);
    if (temp != nullptr) {
        competitorlist->add(temp);
        temp->display();
    }
}




//this function takes a text, uses the inList function to search, returning a true
//if the object is found.
bool Competitors::returnCompetitor(int n) {
    if (competitorlist->inList(n)) 
        return true;
    else
    return false;
}

//returns the competitors nation by competitor ID
char * Competitors::returnNation(int id) {
    Competitor* temp;
    char* nametemp;
    temp = (Competitor*)competitorlist->remove(id);
    competitorlist->add(temp);
    nametemp = new char[strlen(temp->returnNation()) + 1]; strcpy(nametemp, temp->returnNation());
    return nametemp;
}


//takes the competitor ID, removing the object
Competitor* Competitors::getCompetitor(int n) {
    Competitor* temp = (Competitor*)competitorlist->remove(n);
    competitorlist->add(temp);
    return temp;
}

//Returns how many competitors currently registrated to a Nation
int Competitors::currentSquadSize(char *t)	
{	
	int j = 0;
	Competitor* temp;
	int num = competitorlist->noOfElements();
	for (int i = 1; i < num; i++) {				
		temp = (Competitor*)competitorlist->removeNo(i);
		if (temp->isNation(t))				
			++j;								
		competitorlist->add(temp);	
	}
	return j;								// returnerer antall deltagere
}

//reads the "DELTAGERE" file, adding objects to list
void Competitors::read() {
    Competitor* temp;
    int nr = 0;
    ifstream inFile("DELTAGERE.DTA");
    if (inFile) {
        cout << "Reading from DELTAGERE.DTA..." << endl;
        inFile >> nr; inFile.ignore();
        if (nr != 0) {
           while (competitorlist->noOfElements() > 0) {
              delete (Competitor*)competitorlist->remove(1);
           } 
           for (int i = 1; i <= nr; i++) {
               inFile >> id; inFile.ignore();
               if (!competitorlist->inList(id)) {
                   temp = new Competitor(id, inFile); 
                   competitorlist->add(temp);
               }
           }
        }
        else {
            cout << "DELTAGERE.DTA read; contains nothing." << endl;
        }
        
    } else
            cout << "No file named DELTAGERE.DTA..." << endl;
}

//writes objects in list to file
void Competitors::write() {
    int nr = 0;
    Competitor* temp;
    nr = competitorlist->noOfElements();
    
    ofstream outFile("DELTAGERE.DTA");
    outFile << nr << endl;
    for (int i = 1; i <=nr; i++) {
        temp = (Competitor*)competitorlist->removeNo(i);
        temp->write(&outFile);
        competitorlist->add(temp);
    }
    cout << "\nWriting to DELTAGERE.DTA" << endl;
}




