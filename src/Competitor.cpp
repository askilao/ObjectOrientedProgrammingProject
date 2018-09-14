#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "../include/Competitor.h"
#include "../include/ListTool2B.h"
#include "../include/constenum.h"
#include "../include/utilities.h"
#include "../include/global.h"
#include "../include/Nations.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

Competitor::Competitor() { } 

Competitor::Competitor(char* s, int n) : NumElement(n) { //konstruktoren blir kjørt når en ny deltager skal opprettes
    char buffer[STRLEN];                                 
    int nr = 0;
    getInput("Enter Full Name: ", buffer, STRLEN);
    name = new char[strlen(buffer) + 1];  strcpy(name, buffer);
    nr = getInput("Gender: (male = 0, female = 1)", buffer, 0, 1);
    
    switch (nr) {
    case 0: gender = Male; break;
    case 1: gender = Female; break;
    default: break; }
    shortname = s;
  
    nationbase.addCompetitor(shortname, n);
}


Competitor::Competitor(int n, ifstream & in) : NumElement(n) { //om det finnes en fil, vil denne konstruktoren kjøre og 
    char buffer[STRLEN];                                       //lese inn deltagere fra fil, inn i deltagerliste
    int nr = 0;

    in.getline(buffer, STRLEN);
    name = new char[strlen(buffer) + 1];  strcpy(name, buffer);
    in.getline(buffer, STRLEN);
    shortname = new char[strlen(buffer) + 1];  strcpy(shortname, buffer); 
    in >> nr; in.ignore();
    switch (nr) {
    case 0: gender = Male; break;
    case 1: gender = Female; break;
    default: break;
    }
    nationbase.addCompetitor(shortname, n);
   
}

Competitor::~Competitor() {
    delete[] name;
}
 

//lets the user edit competitor attributes; given choices in switch what 
//attribute to edit.
void Competitor::editCompetitor() {
    char buffer[STRLEN];
    char ch;
    cout << "\n\tEdit: "
        << "\nF- Full name"
        << "\nG- Gender"
        << "\nN- Nation" << endl;
    ch = toupper(getInput("> ", buffer));

    switch (ch) {
    case 'F':   
        getInput("Enter Full Name: ", buffer, STRLEN);
        delete[] name;  //navn-pointeren slettes slik at at det ikke blir duplikat av 'name'
        name = new char[strlen(buffer) + 1];  strcpy(name, buffer); break;
    case 'G': {
        int nr = getInput("Gender: (male = 0, female = 1)", buffer, 0, 1);        
        switch (nr) {
        case 0: gender = Male; break; 
        case 1: gender = Female; break; 
        }
    } break;
    case 'N': { 
        char* temp;        
        getIOC("Enter Nation: ", buffer, IOCLEN);
        delete[] shortname; //slettes nåvarende IOC
        temp = new char[strlen(buffer) + 1];  strcpy(temp, buffer);
        while (!nationbase.checkNation(temp)) { //sjekker om IOC finnes
            cout << "That nation is not registered" << endl;
			getIOC("Enter Nation: ", buffer, IOCLEN);
            temp = new char[strlen(buffer) + 1];  strcpy(temp, buffer);
        }
        shortname = temp;
    } break;
    default: cout << "Bad input" << endl;
        break;
    }


}


//displays all competitor attributes to screen.
void Competitor::display() {
    cout << "-----------------------" << endl;
    cout << "Full name: " << name << endl;
    cout << "Gender: "; (gender) ? (cout << "female") : (cout << "male");
    cout << "\nID number: " << number << endl;
    cout << "Nation: " << shortname << endl;
    cout << endl;
}

//
char * Competitor::returnNation() { //returnerer enkelt og greit IOC-navnet hos deltageren
    return shortname;
}


//checks written name to name stored, returns competitor-ID if found.
int Competitor::checkName(char* s) {
    if (!strcmp(s, name)) {
        return number;
    }
    else
        return 0;
}

bool Competitor::isNation(char* s) //tar imot en nasjon, og sjekker om den er lik den lagrede nasjonen
{
	return (shortname == s) ? true : false;
}


//writes competitor-attributes to file.
void Competitor::write(ofstream* out) {
    *out << number    << endl;
    *out << name      << endl;
    *out << shortname << endl;
    (gender) ? (*out << 1) : (*out << 0) << endl;

}

