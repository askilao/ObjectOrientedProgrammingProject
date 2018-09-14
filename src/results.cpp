#include "..\include\results.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

Results::Results(){
}

Results::~Results() {
    delete[] result;
}

Results::Results(int placement, char* s, int id) : NumElement(placement) {
    result = new char[strlen(s) + 1]; strcpy(result, s);
    compid = id;
    //placement er plasseringen som bruker har anngitt, dette blir brukt i medalje og poeng utregning
    switch (placement) {
    case 1: medal = Gold; point = 7; break;
    case 2: medal = Silver; point = 5; break;
    case 3: medal = Bronze; point = 4; break;
    case 4: point = 3; break;
    case 5: point = 2; break;
    case 6: point = 1; break;
    default: medal = Nothing; point = 0; break;
    }
}

void Results::displayResult() {
    cout << "Placement: " << number << endl;
    cout << "Result: " << result << endl;
}

int Results::returnId() {
    return compid; //returnerer deltager ID
}

int Results::returnPlacement() {
    return number; //returnener plassering
}

int Results::returnPoint() {
    return point; // returnerer poeng
}

Medal Results::returnMedal(){
    return medal; //returnerer medalje enumen
}

void Results::writeResult(ofstream & out) {
    out << number << endl;
    out << compid << endl;
    out << result << endl;
}




