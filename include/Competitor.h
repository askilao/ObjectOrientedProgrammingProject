#if !defined(__COMPETITOR_H)           //  Ensures that this file will be
#define __COMPETITOR_H                 //    included only ONCE in each file.

#include <iostream>
#include <fstream>
#include "ListTool2B.h"
#include "constenum.h"

using namespace std;


class Competitor : public NumElement {
    private:
        int id;
        char* name;
        char* shortname;
        char* data;
        Gender gender;

    public:
        Competitor();
        Competitor(char* s, int n);
        Competitor(int n, ifstream & in);
		~Competitor();
        void editCompetitor();   
        void display();
        char * returnNation();
        int checkName(char* s);
		bool isNation(char* s);
        void write(ofstream * out);
};













#endif 