#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "../include/Event.h"
#include "../include/ListTool2B.h"
#include "../include/constenum.h"
#include "../include/utilities.h"
#include "../include/global.h"
#include "../include/Competitors.h"
#include "../include/results.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

Event::Event() {
    cout << "This should never be called" << endl;
}

Event::Event(int n) : NumElement(n) {
    char buffer[STRLEN];
    eventcompetitors = new List(Sorted);
    results = new List(Sorted);

    getInput("Enter Event Name: ", buffer, STRLEN);
    name = new char[strlen(buffer) + 1];  strcpy(name, buffer);
    //antall deltagere er No of elements i deltager listen
    hour = getInput("Enter hour of day: ", buffer, 0, 23);
    min = getInput("Enter minute: ", buffer, 0, 59);

    //ber om år og månede først, lettere å sjekke at dato er riktig da
    year = getInput("Enter year: ", buffer, MINYEAR, MAXYEAR);
    month = getInput("Enter month: ", buffer, 1, 12);

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) //måneder med 31 dager
        day = getInput("Enter day: ", buffer, 1, 31);
    else if (month == 2) { //februar 
        if (year % 400 != 0) //om det ikke er skuddår
            day = getInput("Enter day: ", buffer, 1, 28);
        else
            day = getInput("Enter day: ", buffer, 1, 29);
    }
    else
        day = getInput("Enter day: ", buffer, 1, 30);

    displayDate(day, month, year, hour, min);

}

Event::~Event() {
    delete[] name;
    delete eventcompetitors;
    delete results;
}

List * Event::returnResList()
{
    return results;
}

Event::Event(ifstream & inf, int n) : NumElement(n){
    char buffer[STRLEN];
    eventcompetitors = new List(Sorted);
    results = new List(Sorted);
    
    inf.getline(buffer, STRLEN);
    name = new char[strlen(buffer) + 1];  strcpy(name, buffer);
    inf >> hour; inf.ignore();
    inf >> min; inf.ignore();
    inf >> day; inf.ignore();
    inf >> month; inf.ignore();
    inf >> year; inf.ignore();
}

void Event::addCompetitors() {
    char buffer[STRLEN];
    int nr = 0;
    char ch;
   
    if (!checkList(comp)) {
        compbase.displayAllCompetitors();
        if (compbase.returnList()->noOfElements() != 0) {
            cout << endl;
            do {
                nr = getInput("Add competitor by id number: ", buffer, 0, MAXCOMPETITORS);
                while (!compbase.returnCompetitor(nr)) {
                    cout << "Competitor not found, add by id number" << endl;
                    nr = getInput("Add competitor by id number: ", buffer, 0, MAXCOMPETITORS);
                }
                while (eventcompetitors->inList(nr)) {
                    cout << "Competitor already in list" << endl;
                    nr = getInput("Add competitor by id number: ", buffer, 0, MAXCOMPETITORS);
                }

                eventcompetitors->add(new NumElement(nr));
                
                //add more competitors if wanted
                ch = toupper(getInput("Another one? Y/N: ", buffer));
                while (ch != 'N' && ch != 'Y') {
                    cout << "bad input" << endl;
                    ch = toupper(getInput("Another one? Y/N: ", buffer));
                }

            } while (ch != 'N');
            writeCompetitors();
            cout << "Writing competitors to file" << endl;           
        }
        else
            cout << "No competitors" << endl;
    }
    else
        cout << "Competitors already added, may i suggest edit or display - List?" << endl;
}

void Event::display() {
    int nr = eventcompetitors->noOfElements();
    cout << "\nEvent id: " << number << endl;
    cout << "Event name: " << name << endl;
    cout << "Number of competitors: "<< nr << endl;
    displayDate(day, month, year, hour, min);
    cout << endl;
    //ufullstendig, vet ikke om den skal brukes engang
}


void Event::displayCompetitors() {
    NumElement* temp;
    Competitor* compTemp;
    int nr = eventcompetitors->noOfElements();
    int compID = 0;
    if (nr != 0) {
        cout << "Competitors:" << endl;
            for (int i = 1; i <=nr; i++) {      
                    temp = (NumElement*)eventcompetitors->removeNo(i);
                    if (temp != nullptr) {
                        compID = temp->getNumber();
                        eventcompetitors->add(temp);
                        compTemp = compbase.getCompetitor(compID);
                        compTemp->display();
                        cout << "///////////////////////" << endl;
                    }
        
            }
    }
    else
        cout << "No competitors to display" << endl;
    
    
}
void Event::editCompetitors() {
    int nr;
    char buffer[STRLEN];
    char ch = getInput("Add or remove? A/R", buffer);
    switch (ch) {
    case 'A':
            if (eventcompetitors->noOfElements() < MAXCOMPETITORS)
                addCompetitors();
             else
                cout << "no more room for competitors" << endl;
                break;
    case 'R': 
            displayCompetitors();
            nr = getInput("Who do you want to remove (by id): ", buffer, 1, MAXCOMPETITORS);
            if (eventcompetitors->inList(nr)) {
                eventcompetitors->destroy(nr);
                cout << "User used Remove on" << nr << " It was super effective!" << endl;
                writeCompetitors();
            }

    default: cout << "bad input" << endl;
        break;
    }
}
void Event::removeCompetitors() {
    char filename[STRLEN] = "OV_";
    strcat(filename, name);
    strcat(filename, ".STA");
    
    for(int i = 1; i<=eventcompetitors->noOfElements(); i++)
        delete (NumElement*)eventcompetitors->removeNo(i);
    
    if (remove(filename) != 0)
        cout << "Error deleting " << filename << endl;
    else
        cout << filename << " Deleted" << endl;    
}
void Event::removeResults() {
    char filename[STRLEN] = "OV_";
    strcat(filename, name);
    strcat(filename, ".RES");
    //sletter et objekt til det ikke er flere igjen
    while (results->noOfElements() > 0)
        delete (Results*)results->remove(1);

    if (remove(filename) != 0)
        cout << "Error deleting " << filename << endl;
    else
        cout << filename << " Deleted" << endl;
}
//sjekker om det er noen elementer i listen aka om den er tom
bool Event::checkList(const What_list l) {
    switch (l) {
    case res:  if (results->noOfElements() != 0)
        return true;
               else
                   return false;
        break;
    case comp: if (eventcompetitors->noOfElements() != 0)
        return true;
               else
                   return false;
        break;
    default: break;
    }

}   

void Event::editEvent() {
    char buffer[STRLEN];
    char ch;
    cout << "\n\tEdit: "
        << "\nN- Name"
        << "\nT- Time"
        << "\nD- Date" << endl;
    ch = toupper(getInput("> ", buffer));

    switch (ch) {
    case 'N': 
        getInput("Enter Event Name: ", buffer, STRLEN);
        delete[] name;
        name = new char[strlen(buffer) + 1];  strcpy(name, buffer); 
        break;

    case 'T': 
        hour = getInput("Enter hour of day: ", buffer, 0, 23);
        min = getInput("Enter minute: ", buffer, 0, 59);
        break;

    case 'D': 
        //ber om år og månede først, lettere å sjekke at dato er riktig da
        month = getInput("Enter month: ", buffer, 1, 12);
        year = getInput("Enter year: ", buffer, MINYEAR, MAXYEAR);
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) //måneder med 31 dager
            day = getInput("Enter day: ", buffer, 1, 31);
        else if (month == 2) { //februar 
            if (year % 400 != 0) //om det ikke er skuddår
                day = getInput("Enter day: ", buffer, 1, 28);
            else
                day = getInput("Enter day: ", buffer, 1, 29);
        }
        else
            day = getInput("Enter day: ", buffer, 1, 30);
        break;

    default: break;
    }

}

void Event::addResultlist(Measured_in m, int n, int p) {
    //Enter preciscion 5 for mmsst(true) or 6 for mmsshh(false)
    Results* temp;

    displayCompetitors();
    char buffer[STRLEN];  
    char * result;
    string* str_result = new string();
    int nr = 0;
    int maxplacement = eventcompetitors->noOfElements();
    int placement;
  
    cout << "\nAdd Results:" << endl;
    nr = getInput("Enter id of competitor: ", buffer, 1, MAXCOMPETITORS);
    while(!eventcompetitors->inList(nr)) {
        cout << "Enter valid ID" << endl;
        nr = getInput("Enter id of competitor: ", buffer, 1, MAXCOMPETITORS);
    }
    placement = getInput("Insert placement: ", buffer, 1, maxplacement);
    while (results->inList(placement)) {
        cout << "Placement already taken" << endl;
        placement = getInput("Insert placement: ", buffer, 1, maxplacement);
    }
    // her bruker vi string og string to char * fordi det ble mye lettere å gjøre en int om til en array da
    // får inn m som er en enum defintert ¨når du lager en competition, den sier om resultatet skal være poeng eller tid
    //int p eller n sier hvor mange siffer resultatet skal ha, også defintert når du lager en competition
    switch (m) {
    case times:
        *str_result = to_string(getInput("Enter finish min: ", buffer, 0, 59)) + ":";
        *str_result += to_string(getInput("Enter finish sec: ", buffer, 0, 59)) + ":";      
        if (n == 5) {
            *str_result += to_string(getInput("Enter finish tenth: ", buffer, 0, 10));
         
    }
        else if (n == 6) {
            *str_result += to_string(getInput("Enter finish houndreth: ", buffer, 0, 99));
        }     
        else if (n == 7) {
            *str_result += to_string(getInput("Enter finish thousanth: ", buffer, 0, 999));
        }
        //gjør stringen om til en char * og sender den med plasseringen og deltager id til Results constructoren
        result = new char[str_result->length()+1];
       strcpy(result, str_result->c_str());
        temp = new Results(placement, result, nr);
        results->add(temp);
        break;
    case points:
        //om det er X eller XX
        if (p == 1) {
            *str_result = to_string(getInput("Enter points: ", buffer, 1, 9));
        }
        else if (p == 2) {
            *str_result = to_string(getInput("Enter points: ", buffer, 1, 99));
        }
        result = new char[str_result->length() + 1];
        strcpy(result, str_result->c_str());
        temp = new Results(placement, result, nr);
        results->add(temp);
    default:
        break;
    }
    writeResults();
    
   
}

void Event::displayResults() {
    Results* temp;
    int nr = results->noOfElements();
    int id;
    cout << "Results: " << endl;
    for (int i = 1; i <= nr; i++) {
        temp = (Results*)results->removeNo(i);
        results->add(temp);
        temp->displayResult();
        id = temp->returnId();
        compbase.displayElement(id);      
    }
}

//skriver ut deltager id til fil
void Event::writeCompetitors() {
    //strcat for å sette opp riktig navn eks. OV_EVENTNAME.STA
    char filename[STRLEN] = "OV_";
    strcat(filename, name);
    strcat(filename, ".STA");
    ofstream Ofile(filename);
    NumElement* temp;
    
    int nr = eventcompetitors->noOfElements();
    Ofile << nr << endl;
    for (int i = 1; i <=nr; i++) {
        temp = (NumElement*)eventcompetitors->removeNo(i);
        eventcompetitors->add(temp);
        if (temp != nullptr) {
            Ofile << temp->getNumber() << endl;
        }

    }
  
}
//skriver ut resultat til fil
void Event::writeResults() {
    Results* temp;
    char filename[STRLEN] = "OV_";
        strcat(filename, name);
    strcat(filename, ".RES");
    ofstream Ofile(filename);
    int nr = results->noOfElements();
    if (nr != 0) {
        cout << "Writing to " << filename << endl;
        Ofile << nr << endl;
        for (int i = 1; i <= nr; i++) {
            temp = (Results*)results->removeNo(i);
            results->add(temp);
            temp->writeResult(Ofile);
        }
    }
}
//leser inn resultat fra rett fil
void Event::readResults() {
    Results* temp;
    int nr, placement,id;
    char buffer[STRLEN];
    char * result;
    char filename[STRLEN] = "OV_";
    strcat(filename, name);
    strcat(filename, ".RES");
    ifstream iFile(filename);
    
    if (iFile) {
        cout << "Reading from " << filename << endl;
        iFile >> nr; iFile.ignore();
        for (int i = 1; i <= nr; i++) {
            iFile >> placement; iFile.ignore();
            if (!results->inList(placement)) {
                iFile >> id; iFile.ignore();
                iFile.getline(buffer, STRLEN);
                result = new char[strlen(buffer) + 1]; strcpy(result, buffer);
                temp = new Results(placement, result, id);
                results->add(temp);
            }
        }
    }
    else
        cout << filename << " Not found" << endl;
}
//leser inn deltagerlisten fra fil
void Event::readCompetitors() {

    char filename[STRLEN] = "OV_";
    strcat(filename, name);
    strcat(filename, ".STA");
    ifstream iFile(filename);
    int nr = 0;
    int id;
    if (iFile) {
        cout << "Reading from " << filename << endl;
        iFile >> nr; iFile.ignore();
        while (eventcompetitors->noOfElements() > 0)
            delete (NumElement*)eventcompetitors->remove(1);
        for (int i = 1; i <= nr; i++) {
            iFile >> id; iFile.ignore();
            eventcompetitors->add(new NumElement(id));
        }
    }
    else
        cout << filename << " Not found" << endl;
}
//skriver ut event data, blir kalt av competitions sin skriv
void Event::writeEvent(ofstream & out) {
    out << number << endl;
    out << name << endl;
    out << hour << endl;
    out << min << endl;
    out << day << endl;
    out << month << endl;
    out << year << endl;
}


