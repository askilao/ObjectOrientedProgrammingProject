#if !defined(__MEDALS_H)           //  Ensures that this file will be
#define __MEDALS_H                 //    included only ONCE in each file.

#include "results.h"
#include "Event.h"
#include "ListTool2B.h"


class Medals {
private:
    int gold = 0;
    int silver = 0;
    int bronze = 0;
public:
    Medals();   
    void displayMedals();
    void write(char* s);
    ~Medals();
    

};













#endif 