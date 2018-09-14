#ifndef  __constenum_H
#define __constenum_H


// constenum.h
// Contains all constants and enumerations used throughout project
const int NAMELEN = 21;		// NAME LENGTH OF PERSON	
const int IOCLEN = 4;       //length of country IOC code
const int MAX_EVENTS = 20;      //MAX EVENTS FOR A COMPETITION
const int	STRLEN = 40;		// MAX LENGTH OF 
const int	NATIONLEN = 31;		// NAME LENGTH OF NATION
const int	MAXNATIONS = 201;	// MAX NUMBER OF PARTICIPATING NATIONS
const int	MAXCOMPETITIONS = 51;		// MAX NUMBER OF DIFFERENT	COMPETITIONS
//const int MINCOMPETITORS = 20;		// MIN NUMBER OF COMPETETORS PER NATION
const int	MAXCOMPETITORS = 2000;		// MAX NUMBER OF COMPETETOR PER NATION
const int MAX_LEN_COMPETITION_NAME = 25;	//	MAX LENGTH OF COMPETITION NAME
const int MINPHONE = 11111111;      //LOWEST PHONENUMBER AVAILABLE 
const int MAXPHONE = 99999999;      //HIGHEST PHONENUMBER AVAILABLE
const int MINYEAR = 1900;           //LOWEST YEAR INPUT AVAILABLE 
const int MAXYEAR = 2100;           //HIGHEST YEAR INPUT AVAILABLE



const char MAINMENU[] = "\n\t\tMain Menu : \n\tN- Nation \n\tD- Competitors \n\tG- Competitions \n\tO- Events \n\tM- Medals \n\tP- Points \n\tX- Quit";



enum Medal { Bronze, Silver, Gold, Nothing };			// Used in class Statistics. Bronze = 0, Silver = 1, Gold = 2. 
enum Gender { Male, Female };					// Used in class Competetor. Male = 0, Female = 1.
enum Measured_in { times, points }; //brukt i Competition, for å velge om øvelse måles i poeng eller tid
enum What_list { res, comp }; // brukt i event for å sjekke hvordan liste du vil sjekke
#endif
