#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "../include/Nations.h"
#include "../include/ListTool2B.h"
#include "../include/Nation.h"
#include "../include/constenum.h"
#include "../include/utilities.h"
#include "../include/competitors.h"
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

Nations::Nations() {
    nationlist = new List(Sorted);

}

Nations::~Nations() {
    delete nationlist;
}

List * Nations::returnList() {
    return nationlist;
}



void Nations::registerNation() {
	// Adds whatever instance of Nation is holding
    char buffer[IOCLEN];
    Nation* temp;

    getIOC("Country IOC code: ", buffer, IOCLEN); //international olympic committee 3 letter country code
    shortname = new char[strlen(buffer) + 1];  strcpy(shortname, buffer);

    if (!nationlist->inList(shortname)) {
        temp = new Nation(shortname);
        nationlist->add(temp);
   }
    else
        cout << "That Nation is already registered" << endl;
}

void Nations::display() {
    char buffer[IOCLEN];
    getIOC("Country IOC code: ", buffer, IOCLEN); //international olympic committee 3 letter country code
    shortname = new char[strlen(buffer) + 1];  strcpy(shortname, buffer);
    
    while(!nationlist->inList(shortname)) {
        cout << "ERROR! Couldnt find that nation" << endl;
        getInput("Country IOC code: ", buffer, IOCLEN); 
        shortname = new char[strlen(buffer) + 1];  strcpy(shortname, buffer);
    }
    nationlist->displayElement(shortname);
}
void Nations::limitedDisplay() { // A: skriver alle hoveddata om nasjoner
    Nation* temp;
    int nr = nationlist->noOfElements();
    if (nationlist->noOfElements() != 0) {
        for (int i = 1; i <=nr ; i++) {       
            temp = (Nation*)nationlist->removeNo(i); //tar ut en nation og displayer den
            nationlist->add(temp);
            temp->limitedDisplay();           
        }
    }
    else
        cout << "No nations registered" << endl;
}
void Nations::write() {
    Nation* temp;
    int nr = nationlist->noOfElements();
    
    ofstream oFile("NASJONER.DTA");
    oFile << nr << endl;
    for (int i = 1; i <=nr; i++) {
        temp = (Nation*)nationlist->removeNo(i);
        temp->write(oFile);
        nationlist->add(temp);
    }
}
void Nations::read() {
    Nation* temp;
    char buffer[IOCLEN];
    int nr = 0;
    ifstream iFile("NASJONER.DTA");
    if (iFile) {
        cout << "Reading from NASJONER.DTA....." << endl;
        iFile >> nr; iFile.ignore();
        while (nationlist->noOfElements() > 0)
            delete (Nations*)nationlist->remove(1);

        for (int i = 1; i <= nr; i++) {
            iFile.getline(buffer, IOCLEN);
            shortname = new char[strlen(buffer) + 1];  strcpy(shortname, buffer);
            if (!nationlist->inList(shortname)) {
                temp = new Nation(shortname, iFile);
                nationlist->add(temp);
            }
        }
    }
        else
            cout << "No nations file" << endl;
}
bool Nations::nationSquadSize(char* t) {
	Nation* temp;
	temp = (Nation*)nationlist->remove(t);
	nationlist->add(temp);
    return temp->totalSquad();
}
void Nations::editNation() {
    char buffer[IOCLEN];
    Nation* temp;

    getIOC("Country IOC code: ", buffer, IOCLEN); //international olympic committee 3 letter country code
    shortname = new char[strlen(buffer) + 1];  strcpy(shortname, buffer);
    while (!nationlist->inList(shortname)) {
        cout << "No country by that name registered" << endl;
        getIOC("Country IOC code: ", buffer, IOCLEN); 
        shortname = new char[strlen(buffer) + 1];  strcpy(shortname, buffer);
    }
    temp = (Nation*)nationlist->remove(shortname);
    temp->editNation();
    nationlist->add(temp);
   
}

void Nations::addCompetitor(char * t, int n) {
    Nation* temp;
    temp = (Nation*)nationlist->remove(t);
    temp->addCompetitor(n);
    nationlist->add(temp);
}

bool Nations::checkNation(char * t) {
    if (nationlist->inList(t))
        return true;
    else
        return false;
}

void Nations::displaySquad() {
    char buffer[IOCLEN];
    Nation* temp;

    getIOC("Country IOC code: ", buffer, IOCLEN); //international olympic committee 3 letter country code
    shortname = new char[strlen(buffer) + 1];  strcpy(shortname, buffer);

    temp = (Nation*)nationlist->remove(shortname); // tar ut gitt nasjon
    nationlist->add(temp);                         // setter den tilbake i listen
    temp->displaySquad();                          // skriver ut tempen
}


bool Nations::emptyNation() {
    int nr = nationlist->noOfElements();
    return (nr) ? true : false;
}
