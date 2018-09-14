#ifndef __NATION_H
#define __NATION_H

#include "ListTool2B.h"	//	Base-Class TextElement
#include <iostream>
#include <fstream>
using namespace std;

class Nation : public TextElement {	//TODO
private:
	char shortname[4];	//TODO Skal denne ligge her ? //TODO CONSTANT ? 
	char* longname;
    char* contactname;
	int squadsize;
    int totalcompetitors = 0;
	int contactphone;
    List* competitorIDlist;
    
  

public:
    Nation();
	~Nation();
    Nation(char* s);
    Nation(char* s, ifstream & in);
    char* returnName();
    void editNation(); //lar bruker endre på alt utenom forkortelse og antall i troppen
    void displaySquad();    // skriver ut en nasjons deltagertropp
    void display();  // Skriver ut all data til en gitt nasjon
    void limitedDisplay(); // N A: skriver ut hoveddata
    void addCompetitor(int n); //legger til en competitor i en gitt nasjons sin competitorliste
    void write(ofstream* out); // skriver ut nasjondata til fil (NASJONER.DTA)
    bool totalSquad();	//	Return each nations MAX squad size
    void write(ofstream & out); // skriver ut nasjondata til fil (NASJONER.DTA)


   
       
};

#endif // __NATION_H