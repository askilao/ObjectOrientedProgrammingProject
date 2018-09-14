#ifndef __COMPETITION_H
#define __COMPETITION_H

#include "../include/ListTool2B.h"
#include "../include/constenum.h"
#include "../include/utilities.h"
#include "../include/global.h"
#include "../include/Event.h"
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;


class Competition : public TextElement {
private:
    char* competition_name;
    int competiton_number_of_events;
    int time_precision, point_precision;
    //	Points to all events belong to competition
    List* events;		
    // Points or Time
    Measured_in measured_in;	
public: 
    //	Adds one competition by 'text'
    Competition(char* text);	
    // Adds one competition read from file
    Competition(char* text, ifstream& inf);
	~Competition();
    // Returns a Pointer to eventlist
    List* returnList();
    void startMenu();
    void resultsMenu();
    void editName();
    // Display all data about competition and its events if any
    void display();	
    // Displays competition name and events registrated and how their measured 
    void limitedDisplay();
    // Adds event using 'lastID+1' for generating uniqueID
    void registerEvent();
    // Prompts user for wich data to edit. Usin its id as parameter
    void editEvent();
    // Displays alls events using 'displayList'
    void displayEvent();
    // Displays one event participants
    void displayCompetitors();
    void addCompetitors();
    void editCompetitors();
    bool returnMeasured();
    bool returnPrecision();
    // Writes all data about competitions and their events to file
    void write(ofstream & out);
    // Remove event from list *NB NO REUSE OF THIS ID IS POSSIBLE*
    void removeEvent();
};
#endif // !__COMPETITION_H
