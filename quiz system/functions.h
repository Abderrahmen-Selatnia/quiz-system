#ifndef FUNCTIONS_H
#define FUNCTIONS_H
typedef struct user
{
    char username[32];
    char password[32];
    int score;
    int id;
}user ;

int  greeting();

int checker(char u[], const char filename[]);
int findlinenumber(char valuetochek[], const char filename[]);
int spisifiedlinecheck(char tochek[], int lineN, const char filename[]);
int usernamevalidation(user *p, char username[]);
int passwordvalidation(char p[]);
int addinstruct(user *p, int id, char password[], char username[]);
int login(user *p, char username[], char password[]);
int findidforenw(user *p);
int signup(user *ptr, char u[], char p[]);
int deletee(const char filename[], char valuetoD[]);
int edit(const char filename[], char valuetoD[], char newvalue[]);
int howmanyline(const char filename[]);
int quizing(char username[]);
int chekanswer(char answer[], int Qlinenumber);
int scorcaculator(int answerscor, int *result, int *secsesif);
int userpassdeleter(char u[]);
int printer(const char filename[]);
int loginusingstruct(user *p, int id);
void deleteuserS(user *p, int id);
void edituserS(user *p, int id);
int userid(user *p, char username[], int maxusers);
int fileloader(const char filename[], user **ptr, int *currentsize);
int loginstructv2(user *ptr, char username[], char password[], int MAXUSERS);

#endif