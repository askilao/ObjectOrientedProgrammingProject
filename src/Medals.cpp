

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "../include/Medals.h"
#include "../include/ListTool2B.h"
#include "../include/constenum.h"
#include "../include/utilities.h"
#include "../include/global.h"
#include "../include/Nation.h"
#include "../include/Competition.h"
#include <iostream>
#include <cstring>


Medals::Medals() {
   
}

Medals::~Medals()
{
}

void Medals::displayMedals() {
    Nation* nationtemp;
    Competition* comptemp;
    Event* eventtemp;
    Results* resulttemp;
    char* nationame;
   
   //for-løkker som i bunn og grunn henter ut en nasjon og sammenligner den nasjonen med en deltager som har vunnet medaljes nasjon.
    // om nasjonene stemmer så skal det telles opp medaljer ut fra hva som ble lagret i Results
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
                            if (resulttemp->returnMedal() == Gold)
                                gold++;
                            if (resulttemp->returnMedal() == Silver)
                                silver++;
                            if (resulttemp->returnMedal() == Bronze)
                                bronze++;
                        }
                    

                }
            }
        }
        if (gold > 0 || silver > 0 || bronze > 0) {
            cout << nationtemp->returnName() << ":" << endl;
            cout << "Gold: " << gold << endl;
            cout << "Silver: " << silver << endl;
            cout << "Bronze: " << bronze << endl;
            cout << "---------------------" << endl;
            write(nationtemp->returnName());
        }

            gold = 0;
            silver = 0;
            bronze = 0;
        
    }
    
    
}

void Medals::write(char* s) {
    ofstream out("MEDALS.DTA");
    cout << "printing to MEDALS.DTA" << endl;
    out << s << endl;
    out << "Gold: " << gold << endl;
    out << "Silver: " << silver << endl;
    out << "Bronze: " << bronze << endl;
}
