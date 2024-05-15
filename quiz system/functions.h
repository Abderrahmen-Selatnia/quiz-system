#ifndef FUNCTIONS_H
#define FUNCTIONS_H
typedef struct user
{
    char username[32];
    char password[32];
    int score;
    int id;
}user ;

int greeting();



int spisifiedlinecheck(char tochek[50], int lineN, const char filename[]);



int delete(const char filename[15], char valuetoD[]);

int edit(const char filename[15], char valuetoD[500], char newvalue[500]);

int howmanyline(const char filename[15]);
int quizing(char username[]);

int chekanswer(char answer[500], int Qlinenumber);

int scorcaculator(int answerscor, int *result, int *secsesif);

int userpassdeleter(char u[40]);

int printer(const char filename[]);
int passwordvalidation(char p[40]);
int loginusingstruct(user *pn, char *username, char *password);
void edituserS(user *p, int id) void deleteuserS(user *p, int id)
int usernamevalidation(char *username);
int findidforenw(user *p);
int addinstruct(user *p, int id, char *password[], char *username[]);
int loginusingstruct(user *p, int id);
int userid(char username[], int *id);

#endif