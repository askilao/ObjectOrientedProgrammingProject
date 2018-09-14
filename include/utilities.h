#ifndef __UTILITIES_H
#define __UTILITIES_H
char getInput(char t[], char s[]); // trenger tekst og buffer
void getInput(char t[], char s[], const int LEN); // trenger tekst, buffer og stringlength
void getIOC(char t[], char s[], const int LEN);
int getInput(char t[], char s[], int MIN, int MAX); // trenger tekst, buffer og min, max
bool numCheck(char s[]);
void displayDate(int day,int month,int year,int hour,int min);

#endif // !__UTILITIES_H
