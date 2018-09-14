#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "../include/Points.h"
#include "../include/ListTool2B.h"
#include "../include/constenum.h"
#include "../include/utilities.h"
#include "../include/utilities.h"
#include "../include/global.h"
#include "../include/Nation.h"
#include "../include/Competition.h"
#include <iostream>
#include <cstring>
using namespace std;

Points::Points() {
    pointlist = new List(FIFO);

}

Points::~Points() {
    delete pointlist;
}

void Points::displayPoints() {
    Nation* nationtemp;
    Competition* comptemp;
    Event* eventtemp;
    Results* resulttemp;
    char* nationame;


    //går gjennom alle nasjoner og sammenligner med en deltager som har vunnnet medaljes nasjon
    //om det stemmer hentes poeng ut og plusses på for og så displayes
    for (int i = 1; i <= nationbase.returnList()->noOfElements(); i++) {
        nationtemp = (Nation*)nationbase.returnList()->removeNo(i);
        nationbase.returnList()->add(nationtemp);

        for (int i = 1; i <= cbase.returnList()->noOfElements(); i++) {
            comptemp = (Competition*)cbase.returnList()->removeNo(i);
            cbase.returnList()->add(comptemp);

            for (int i = 1; i <= comptemp->returnList()->noOfElements(); i++) {
                eventtemp = (Event*)comptemp->returnList()->removeNo(i);
                comptemp->returnList()->add(eventtemp);

                for (int i = 1; i <= eventtemp->returnResList()->noOfElements(); i++) {
                    resulttemp = (Results*)eventtemp->returnResList()->removeNo(i);

                    eventtemp->returnResList()->add(resulttemp);
                    

                    nationame = compbase.returnNation(resulttemp->returnId());
                    if (strcmp(nationame, nationtemp->returnName()) == 0) {
                        point += resulttemp->returnPoint();
                    }


                }
            }
        }
        if (point > 0) {
            cout << nationtemp->returnName() << ":" << endl;
            cout << "Point: " << point << endl;
            write(nationtemp->returnName());
        }
        point = 0;

    }
}

void Points::read()
{
}

void Points::write(char* s) {
    ofstream out("POINTS.DTA");
    cout << "Writing to POINTS.DTA" << endl;
    out << s << endl;
    out << "point: " << point << endl;
}


