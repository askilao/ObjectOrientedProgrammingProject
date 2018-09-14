

#if !defined(__COMPETITORS_H)           //  Ensures that this file will be
#define __COMPETITORS_H                 //    included only ONCE in each file.


#include "ListTool2B.h"
#include <fstream>
#include <iostream>
#include "Competitor.h"
using namespace std;



class Competitors {
    private:
        int id;
        List* competitorlist;               

    public:
        Competitors();
        ~Competitors();
        List* returnList();
        void registerCompetitor();     
        void editCompetitor();
        void displayAllCompetitors();
        void displayElement();
        void displayElement(int id);
        bool returnCompetitor(int n);
        char* returnNation(int id);
        Competitor* getCompetitor(int n);
        int currentSquadSize(char *t);
        void read();
        void write();
};














#endif 