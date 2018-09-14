#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "../include/Competition.h"
#include "../include/Competitions.h"
#include "../include/global.h"

Competition::Competition(char * text) : TextElement(text) {
	char buffer[STRLEN];
	int nr;
	events = new List(Sorted);
	competition_name = new char[strlen(text) + 1];
	strcpy(competition_name, text);

	nr = getInput("Measured by? 0(Time) or 1(Points)", buffer, 0, 1);
	if (nr == 0) {
		measured_in = times; time_precision = getInput("Enter preciscion: (5) for MMSST, (6) for MMSSHH or (7) for MMSSHHH", buffer, 5, 7);
	}
    else if(nr == 1) {
        measured_in = points; point_precision = getInput("Enter preciscion: (1) for X or (2) for XX", buffer, 1, 2);
    }
}

Competition::Competition(char * text, ifstream & inf) : TextElement(text) {
    events = new List(Sorted);
    Event* temp;
	int nr = 0;
    int eventid;
    int eventnr;
	competition_name = new char[strlen(text) + 1]; strcpy(competition_name, text);

	inf >> nr; inf.ignore();
    if (nr==0) {
        inf >> time_precision; inf.ignore();
    }
    else if (nr==1) {
        inf >> point_precision; inf.ignore();
    }


	if (nr == 1)
		measured_in = points;
	 else if(nr == 0)
         measured_in = times;
    inf >> eventnr; inf.ignore();
    if (eventnr != 0) {
        for(int i = 1; i<=eventnr; i++){
        inf >> eventid; inf.ignore();
        if (!events->inList(nr)) {
            temp = new Event(inf, eventid);
            events->add(temp);
        }
        }
    }
}

Competition::~Competition() {
    delete[] competition_name;
}

List * Competition::returnList(){
    return events;
}

void Competition::startMenu() {
    char ch;
    char buffer[STRLEN];
    Event* temp;
    displayEvent();
    int nr = getInput("Enter event id: ", buffer, 1000, lastID);
    if (events->inList(nr)) {
        temp = (Event*)events->remove(nr);
        events->add(temp);
        temp->readCompetitors();

        cout << "\n\t Starter Menu:"
            << "\n\tS- Print Starter List "
            << "\n\tN- New Starter List"
            << "\n\tE- Edit Starter List"
            << "\n\tF- Remove Starter List and Local Data"
            << "\n\tQ- Return to Main Menu" << endl;

        ch = toupper(getInput("> ", buffer));
        while (ch != 'Q') {
            switch (ch) {
            case 'S': temp->displayCompetitors(); break;
            case 'N': temp->addCompetitors(); break;
            case 'E': temp->editCompetitors(); break;
            case 'F': temp->removeCompetitors(); break;
            case 'Q':  break;
            default: cout << "bad input" << endl;
                break;
            }
            cout << "\n\t Starter Menu:"
                << "\n\tS- Print Starter List "
                << "\n\tN- New Starter List"
                << "\n\tE- Edit Starter List"
                << "\n\tF- Remove Starter List and Local Data"
                << "\n\tQ- Return to Main Menu" << endl;
            ch = toupper(getInput("> ", buffer));
        }
    }
}

void Competition::resultsMenu() {
    char ch;
    char buffer[STRLEN];
    Event* temp;
    displayEvent();
    int nr = getInput("Enter event id: ", buffer, 1000, lastID);
    if (events->inList(nr)) {
        temp = (Event*)events->remove(nr);
        events->add(temp);
        temp->readResults();

        cout << "\n\tResult Menu:"
            << "\n\tS- Print Results"
            << "\n\tN- New Result List"
            << "\n\tF- Remove Result List and Local Data"
            << "\n\tQ- Return to Main Menu" << endl;

        ch = toupper(getInput("> ", buffer));
        while (ch != 'Q') {
            switch (ch) {
            case 'S':temp->displayResults();  break;
            case 'N':temp->addResultlist(measured_in, time_precision, point_precision); break;
            case 'F':temp->removeResults();  break;
            case 'Q':  break;
            default: cout << "bad input" << endl;
                break;
            }
            ch = toupper(getInput("> ", buffer));
        }
    }
}

void Competition::editName() {
	char buffer[MAX_LEN_COMPETITION_NAME];
	getInput("Enter new Name for competition", buffer, MAX_LEN_COMPETITION_NAME);
	competition_name = new char[strlen(buffer) + 1];
	strcpy(competition_name, buffer);
}

void Competition::display() {
	cout << "-----------------------" << endl;
	cout << "Competition name: " << text << endl;
	cout << "Measured in: " << (measured_in) ? "Number" : "Points\n";
	if (!events->isEmpty() )
		events->displayList();
	else cout << "\nNo event(s) registrated" << endl;
}

void Competition::limitedDisplay() {
	cout << "-----------------------" << endl;
	cout << "Competition name: " << text << endl;
	cout << "Number of events registred: " << events->noOfElements() << endl;
	cout << "Measured in: ";
    if (measured_in == points) cout << "Points" << endl;
    else cout << "Time" << endl;
        cout << "Precision: ";
        if (time_precision == 5)
            cout << "mmsst" << endl;
        else if (time_precision == 6)
            cout << "mmsshh" << endl;
        else if (time_precision == 7)
            cout << "mmsshhh" << endl;
        else if (point_precision == 1)
            cout << "x" << endl;
        else if (point_precision == 2)
            cout << "xx" << endl;
}

void Competition::registerEvent() {
    Event* temp;
    int nr;
    if (events->noOfElements() < MAX_EVENTS) {
        nr = ++lastID;
        temp = new Event(nr);
        events->add(temp);
    }
    else
        cout << "This competition has reached max limit of 20 events." << endl;
}


void Competition::editEvent() {
    char buffer[STRLEN];
    Event* temp;
    events->displayList();

    int nr = getInput("Enter event ID: ", buffer, 1000, lastID);
    if (events->inList(nr)) {
        temp = (Event*)events->remove(nr);
        temp->editEvent();
        events->add(temp);
    }
    else
        cout << "Event not found " << endl;

}

void Competition::displayEvent() {
    cout << "\nEvents: " << endl;
    events->displayList();
}

void Competition::displayCompetitors() {
    char buffer[STRLEN];
    Event* temp;
    int nr = getInput("Enter event id: ", buffer, 1000, lastID);
    if (events->inList(nr)) {
        temp = (Event*)events->remove(nr);
        events->add(temp);
        temp->displayCompetitors();
    }
    else
        cout << "Couldnt find event" << endl;
}

void Competition::addCompetitors() {
    char buffer[STRLEN];
    Event* temp;
    int nr = getInput("Enter event id: ", buffer, 1000, lastID);
    if (events->inList(nr)) {
        temp = (Event*)events->remove(nr);
        events->add(temp);
        if (!temp->checkList(comp))
            temp->addCompetitors();
        else
            cout << "List already exists" << endl;
    }
    else
        cout << "Couldnt find event" << endl;
}

void Competition::editCompetitors() {
    char buffer[STRLEN];
    Event* temp;
    int nr = getInput("Enter event id: ", buffer, 1000, lastID);
    if (events->inList(nr)) {
        temp = (Event*)events->remove(nr);
        events->add(temp);
        if (!temp->checkList(res))
            temp->editCompetitors();
        else
            cout << "cant edit, because results are already logged" << endl;
    }
    else
        cout << "Couldnt find event" << endl;
}

bool Competition::returnMeasured() {
    if (measured_in == times) // true = time
        return true;
    else if (measured_in == points)
        return false; //false = points
}

bool Competition::returnPrecision() {
    //Enter preciscion 5 for mmsst or 6 for mmsshh
    if (time_precision == 5)
        return true;
    else if (time_precision == 6)
        return false;
}

void Competition::write(ofstream & out) {
    int nr = events->noOfElements();
    Event* temp;
	out << competition_name << endl;
    out << measured_in << endl;
    if (measured_in == times)
        out << time_precision << endl;
    else if (measured_in == points)
        out << point_precision << endl;
    out << nr << endl;
    if (nr != 0) {
        for (int i = 1; i <= nr; i++) {
            temp = (Event*)events->removeNo(i);
            temp->writeEvent(out);
            events->add(temp);
        }
    }
}

// Deleting event results in permanent removing the use of that ID
void Competition::removeEvent() {
    char buffer[STRLEN];
    Event* temp;
    int nr = getInput("Which event to delete?", buffer, 1000, lastID);

    if (events->inList(nr)) {
        temp = (Event*)events->remove(nr);
        temp->removeCompetitors();
        temp->removeResults();
        events->destroy(nr);
        cout << "\nEvent deleted." << endl;
    }
    else
        cout << "No event by this ID" << endl;    
}
