#if !defined(__EVENT_H)           //  Ensures that this file will be
#define __EVENT_H                 //    included only ONCE in each file.
#include "ListTool2B.h"
#include "Competitor.h"
#include <string>


class Event : public NumElement {
protected:
    char* name;
    int competitors = 0;
    int hour, min, day, month, year; //hour, min, day , month, year er for dato innlesning
    List* eventcompetitors;                       
    List* results;
    What_list list;

public:
    //void editEvent();
    //void displayAllEvents();
    //void displayEvent();
	Event();
    Event(int n);
	~Event();
    List* returnResList();
    Event(ifstream & inf, int n);
    void addCompetitors(); // legger til deltagere i deltagerlisten 
    void display(); //skriver ut event data
    void displayCompetitors(); // skriver ut deltagere i deltagerlisten
    void editCompetitors(); // kan fjerne eller legge til noen i deltagerlisten
    void removeCompetitors(); // fjerner deltagerlisten og sletter fil
    void removeResults(); // fjerner resultatlisten og sletter fil
    bool checkList(const What_list l); // sjekker om det er noen i deltager eller resultat listen, utifra enumen
    void write(); // skriver event til fil, blir kalt på¨av competition sin write
    void writeCompetitors(); // skriver ut deltagerlisten   
    void readCompetitors(); // leser inn deltagerlisten
    void editEvent();
    void writeEvent(ofstream & out);
    void addResultlist(Measured_in m, int n, int p);
    void displayResults();
    void readResults();
    void writeResults();
    char* returnName();

};














#endif 