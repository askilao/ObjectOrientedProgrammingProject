#if !defined(__COMPETITIONS_H)           //  Ensures that this file will be
#define __COMPETITIONS_H                 //    included only ONCE in each file.

#include "../include/ListTool2B.h"

class Competitions {
private:
	char* competition_name;
    char* test;
	List* competitions;	
public:
	Competitions();
	~Competitions();
    List* returnList();
    void eventMenu();
	void display();
	void addCompetition();
	void editCompetition();
	void limitedDisplay();	//	Displays data for ALL competitons
	void displayCompetition();	//	Displays data for ONE competition and its event data
	void read();
	void write();

};
#endif 