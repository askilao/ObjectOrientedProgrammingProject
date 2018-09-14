#if !defined(__RESULTS_H)           //  Ensures that this file will be
#define __RESULTS_H                //    included only ONCE in each file.

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "ListTool2B.h"
#include "constenum.h"
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;


class Results : public NumElement {
private:
    char* result;
    int compid; 
    int point;
    Medal medal;
public:

    Results();
	~Results();
    Results(int placement, char * s, int id);
    void displayResult();
    int returnId();
    int returnPlacement();
    int returnPoint();
    Medal returnMedal();
   
    bool checkPlacement(int n);
    void writeResult(ofstream & out);
};












#endif 