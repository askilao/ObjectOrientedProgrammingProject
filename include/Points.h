#if !defined(__POINTS_H)           //  Ensures that this file will be
#define __POINTS_H                 //    included only ONCE in each file.

#include "ListTool2B.h"


class Points {
private:
    List* pointlist;
    int point = 0;

public:
    Points();
    ~Points();
    void displayPoints();
    void read();
    void write(char* s);
};

















#endif 