#ifndef Gruppe01_NATION_H
#define Gruppe01_NATION_H


#include "ListTool2B.h"	// Using Linked-List datastructure. add() remove() ...	//TODO fyll inn alle vi bruker
#include <fstream>
using namespace std;
class Nations {
private:
    char* shortname;
	List* nationlist;	//	A pointer to first(HEAD) of the list
public:
    Nations();
    ~Nations();
    List* returnList();
	void registerNation(); // lar deg registrere en nasjon og legge den til i lista
    void display(); //skriver ut alle nasjoner
    void editNation();
    void addCompetitor(char* t, int n);
    bool checkNation(char* t);
    void displaySquad(); // skriver ut deltagere i en gitt tropp
    bool emptyNation();
    void limitedDisplay(); //skriver ut alle nasjoner sin hoveddata
    void write();
    void read();
	bool nationSquadSize(char* t); //sjekker om det er plass til flere deltagere i en nasjon, utifra squadsize
};


#endif // !Gruppe01_NATION_H 