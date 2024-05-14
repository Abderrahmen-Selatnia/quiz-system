int greeting();

int login();

int checker(char u[30], const char filename[15]);

int spisifiedlinecheck(char tochek[50], int lineN, const char filename[]);

int signup(upoint);

int delete(const char filename[15], char valuetoD[]);

int edit(const char filename[15], char valuetoD[500], char newvalue[500]);

int howmanyline(const char filename[15]);
int quizing(char upointname[]);

int chekanswer(char answer[500], int Qlinenumber);

int scorcaculator(int answerscor, int *result, int *secsesif);

int upointpassdeleter(char u[40]);

int printer(const char filename[]);

int structvalexistance(upoint,const char atribut[10], char scanedvalue[40]);

int structwriter(upoint, int id, const char atribut[10], void value);

int write_int(upoint, int id, const char atribut[10], int value);

int write_string(upoint, int id, const char atribut[10], char value[50]);

int passwordvalidation(char p[40]);
int loginusingstruct(upoint);