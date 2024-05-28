#include <stdio.h>
#include <strings.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXUSERS 1000

typedef struct user
{
    char username[32];
    char password[32];
    int score;
    int id;
} user;

void greeting()
{

    printf("################## Hello, welcome to the Quizing system ######################\n press enter to sing in else \n 'n' to sing up ");
}

int findlinenumber(char valuetochek[500], const char filename)
{

    int linenumber = 1;
    char tempval[300];

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("error opning file");
        return -1;
    }

    while (fscanf(filename, "s", tempval) != 0)
    {

        if (tempval == valuetochek)
        {

            return linenumber;
        }
        linenumber++;
    }
    return -1;
}

int login(user *p, char *username[], char *password[])
{
    int Uline = 0, tryes = 1;
    char tempu[30], tempp[30];
    printf("please enter your username: \n>");
    fgets(tempu, sizeof(tempu), stdin);
    if (strcmp("admin", tempu) == 0)
    {
        printf("Now please type the password: \n>");

        FILE *fpp = fopen("password.txt", "r");

        if (fpp == NULL)
        {
            printf("could not open file ");
            return -1;
        }
        fgets(tempp, sizeof(tempp), stdin);
        do
        {
            fscanf(fpp, "%s", &password);

            Uline = findlinenumber(&password, "passwords");
            if (strcasecmp(*password, tempp) == 0 && Uline != -1)
            {
                printf("welcome admin\n");
                fgets(*username, sizeof(*username), tempu);
                return 1;
            }
            else
            {
                printf("wrong password try again (%d tryes left) please:\n>", 4 - tryes);
                tryes++;
            }
        } while (strcasecmp(*password, tempp) != 0 && tryes < 4);
    }
    else
    {
        if (checker(tempu, "users.txt") != 0)
        {
            Uline = checker(tempu, "users.txt");
            printf("Now please type the password: \n>");

            FILE *fpp = fopen("password.txt", "r");
            if (fpp == NULL)
            {
                printf("could not open file ");
                return -1;
            }

            do
            {
                fgets(tempp, sizeof(tempp), stdin);
                if (spisifiedlinecheck(tempp, Uline, "paswords.txt"))
                {
                    printf("welcome");
                    fgets(*username, sizeof(*username), tempu);
                    return 2;
                }
                else
                {
                    printf("wrong password try again (%d tryes left) please:\n>", 4 - tryes);
                    tryes++;
                }
            } while (strcasecmp(*password, tempp) != 0 && tryes < 4);
        }
    }
}

int signup(user *ptr, char *u[40], char *p[40])
{
    int tryes = 4;

    printf("please enter your username");
    scanf("%s", u);
    if (checker(u, "users.txt") == 0)
    {
        FILE *fileu = fopen("user.txt", "a+");
        if (fileu == NULL)
        {
            printf("error opening file");
            return -1;
        }
        else
        {
            fprintf(fileu, "%s\n", u);
            fclose(fileu);
            return 1;
        }
    }
    else
    {

        FILE *fileu = fopen("user.txt", "a+");
        if (fileu == NULL)
        {
            printf("error opening file");
            return -1;
        }
        else
        {
            if (checker(u, "users.txt") != 0 && tryes > 0)
            {
                printf("please enter a valid username \n>");
                scanf("%s", u);

            
            

                do
                {
                    
                    
                    tryes--;

                } while (checker(u, "users.txt") != 0 && tryes > 0);
            }else
            {
                fprintf(fileu, "%s\n", u);
                fclose(fileu);
                return 1;
            }
            

            
        }

        fprintf(fileu, "%s\n", u);
        fclose(fileu);
        return 1;
    }

    printf("please enter your password");
    scanf("%s", p);
    if (passwordvalidation(p))
    {
        FILE *file = fopen("password.txt", "a+");
        if (file == NULL)
        {
            printf("error opening file");
            return -1;
        }
        else
        {
            fprintf(file, "%s\n", p);
            fclose(file);
            return 1;
        }
    }
    else
    {

        do
        {
            printf("please try again and try with valid password\n>");
            scanf("%s", &p);
        } while (!passwordvalidation(p));
    }

    addinstruct(ptr, userid(ptr, findidforenw(ptr)), p, u);
}

int checker(char u[30], const char filename[15])
{

    int linenumber = 1;
    FILE *file;
    char tempcmpusername[30];
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("could not check the username properly");
        return -1;
    }
    while (fscanf(file, "%s", tempcmpusername) != 0)
    {

        if (strcmp(u, tempcmpusername) == 0)
        {

            printf("user name is already taken");
            return linenumber;
            break;
        }
        linenumber++;
    }
    printf("username is not taken yet");
    return 0;
    fclose(file);
}

int spisifiedlinecheck(char tochek[50], int lineN, const char filename[])
{

    int checkstoper = 1, linenumber = 1;
    char temp[32];
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {

        printf("could not open file ");
        return -1;
    }
    else
    {
        int linenumber = 1;
        FILE *file = fopen(filename, "r");

        if (file == NULL)
        {
            printf("Error opening file: %s\n", filename);
            return -1;
        }

        while (fscanf(file, "%s", temp) != 0)
        {
            if (linenumber == lineN && strcmp(tochek, temp) == 0)
            {
                fclose(file);
                return 1; // String found on the specified line
            }
            linenumber++;
        }

        fclose(file);
        return 0; // String not found in the file
    }
}

int deletee(const char filename[15], char valuetoD[])
{
    const char tempfile[15];
    char readingtemp[50];

    strcpy(tempfile, filename);
    strcat(tempfile, "tempC");
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen(tempfile, "w");
    if (file == NULL || temp == NULL)
    {
        printf("error opning a file ");
        return -1;
    }
    else
    {
        while (fscanf(file, "s", readingtemp) != 0)
        {
            if (strcasecmp(readingtemp, valuetoD) == 0)
            {
                continue;
            }
            else
            {
                fprintf(temp, "s\n", readingtemp);
            }
        }
        if (checker(valuetoD, filename) == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int edit(const char filename[15], char valuetoD[500], char newvalue[500])
{

    const char tempfile[15];
    char readingtemp[500];

    strcpy(tempfile, filename);
    strcat(tempfile, "tempC");
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen(tempfile, "w");
    if (file == NULL || temp == NULL)
    {
        printf("error opning a file ");
        return -1;
    }
    else
    {
        while (fscanf(file, "s", readingtemp) != 0)
        {
            if (strcasecmp(readingtemp, valuetoD) == 0)
            {
                fprintf(temp, "s", newvalue);
            }
            else
            {
                fprintf(temp, "s\n", readingtemp);
            }
        }
        if (checker(valuetoD, filename) == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int howmanyline(const char filename[15])
{
    int linenumber = 1;
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("error opning a file");
        return -1;
    }

    while (feof(file) != 0)
    {
        linenumber++;
    }
    return linenumber;
}
int quizing(char username[])
{

    int line, linenumber = 1;
    char tempQ[300];
    srand(time(NULL));
    line = rand() % (howmanyline("questions"), 1);
    FILE *file = fopen("questions", "r");
    if (file == NULL)
    {
        printf("error opning file");
        return -1;
    }

    while (fscanf("questions", "s", tempQ) != 0)
    {

        if (linenumber == line)
        {
            fprintf(tempQ, "s", stdout);
            break;
        }
        linenumber++;
    }
    return linenumber;
}
int chekanswer(char answer[500], int Qlinenumber)
{
    FILE *file = fopen("aswers", "r");
    if (file == NULL)
    {
        printf("error opning a file ");
        return -1;
    }
    char rightA[500], tempA[500];

    int linenumber = 1;
    while (fscanf(file, "s", &tempA))
    {
        if (strcmp(tempA, answer) == 0 && linenumber == Qlinenumber)
        {
            strcpy(rightA, tempA);
            printf("right answer \n>");
            return 1;
        }
        else
        {
            printf("wrong answer \n>");
            printf("ther right answer was :%s", rightA);
            return 0;
        }
        linenumber++;
    }
}
int scorcaculator(int answerscor, int *result, int *secsesif)
{

    if (answerscor = 0)
    {
        *result -= *secsesif;
        *secsesif = 0;
        printf("that is not the right way son \n");
    }
    else
    {
        *result++;
        *secsesif++;
    }
    if ((10 - *secsesif) == 7)
    {
        printf("i like your spirit \n>");
    }
    else if ((10 - *secsesif) == 4)
    {
        printf("%d one after another you are the best \n>", 10 - *secsesif);
    }
    else if (10 - *secsesif == 0)
    {
        printf("respect +  you are a nerd \n");
    }

    *result += *secsesif;
    return *result;
}
int userpassdeleter(char u[40])
{
    int Uline;
    char temppass[40];
    int line = 1;
    Uline = checker(u, "users.txt");

    FILE *fpp = fopen("password.txt", "r");
    if (fpp == NULL)
    {
        printf("could not open file ");
        return -1;
    }

    do
    {

        if (Uline == line)
        {
            deletee("paswwords.txt", temppass);
        }
        else
        {
            line++;
        }
    } while (fscanf(fpp, "%s", temppass) != 0);
}
int printer(const char filename[])

{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("error opning file ");
    }

    while (feof != 0)
    {
        fprintf(file, " %s\n", stdout);
    }
}

int passwordvalidation(char p[40])
{

    bool hasnumber = false;
    bool hasspecialcharacter = false;
    bool haslowercharcter = false;
    bool redcuiredlengh = false;
    bool hasasymbole = false;
    if (strlen(p) < 8)
    {
        printf("password must be at least 8 characters long\n");
        return -1;
    }

    for (int i = 0; i < strlen(p); i++)
    {

        if (isupper((p + i)))
        {
            hasspecialcharacter = true;
        }
        if (islower((p + i)))
        {
            haslowercharcter = true;
        }
        if (isdigit((p + i)))
        {
            hasnumber = true;
        }
        if (ispunct((p + i)))
        {
            hasasymbole = true;
        }
    }
    if (!hasasymbole)
    {
        printf("your password must have a symbole");
        return 0;
    }
    if (!haslowercharcter)
    {
        printf("your password must have a lowercase char");

        return 0;
    }
    if (!hasspecialcharacter)
    {
        printf("your password must have a capital letter");

        return 0;
    }
    if (!hasnumber)
    {
        printf("your password must have a number");

        return 0;
    }
    return 1;
}
int loginusingstruct(user *p, int id)
{
    int triesLeft = 4;
    char password[20];

    do
    {
        printf("Enter password (you have %d tries left): ", triesLeft);
        scanf("%s", password);

        if (strcmp((p + id)->password, password) == 0)
        {
            printf("Login successful!\n");
            return 1;
        }
        else
        {
            printf("Incorrect password. ");
            triesLeft--;
        }

        if (triesLeft == 0)
        {
            printf("You have no tries left. Exiting...\n");
            return 0;
        }

    } while (triesLeft > 0);

    return 0;
}

int addinstruct(user *p, int id, char *password[], char *username[])
{
    
    
    if (!usernamevalidation(&username))
    {
        do
        {
            printf("please enter a valid username");
            scanf("%s", *username);

        } while (!usernamevalidation(*username));
    }
    else
    {

        strcpy((p + id)->username, &username);
    }

    printf("enter password");
    scanf("%s", &password);

    if (!passwordvalidation(&password))
    {
        do
        {
            printf("please enter a valid password");
            scanf("%s",&password);

        } while (!passwordvalidation(&password));
    }
    else
    {

        strcpy((p + id)->password,&password);
    }

    return 1;
}
int findidforenw(user *p)
{

    for (int i = 0; i < MAXUSERS; i++)
    {
        if ((p + i)->id = 0)
        {
            return i;
        }
    }
}
int usernamevalidation(user *p, char *username)
{
    for (int i = 0; i < MAXUSERS; i++)
    {
        if (strcasecmp((p + i)->username, &username) == 0)
        {
            return 1;
            break;
        }
    }

    return 0;
}
void deleteuserS(user *p, int id)
{
    if ((p + id)->id != 0)
    {
        (p + id)->id = 0;
        strcpy((p + id)->username, '0');
        strcpy((p + id)->password, '0');
        (p + id)->score = 0;
        printf("User deleted successfully.\n");
    }
    else
    {
        printf("User with ID %d not found.\n", id);
    }
}
void edituserS(user *p, int id)
{
    if ((p + id)->id != 0)
    {

        char stemp[50];
        printf("Enter new username: ");
        scanf("%s", stemp);
        if (strcasecmp(stemp, '\n') != 0)
        {

            scanf("%s", (p + id)->username);
        }
        printf("Enter new password: ");
        scanf("%s", stemp);
        if (strcasecmp(stemp, '\n') != 0)
        {

            scanf("%s", (p + id)->password);
        }

        printf("User details updated successfully.\n");
    }
    else
    {
        printf("User with ID %d not found.\n", id);
    }
}
int userid(user *p, char username[])
{
    for (int i = 0; i < MAXUSERS; i++)
    {
        if (strcmp((p + i)->username, username) == 0)
        {
            return i;
        }
    }
    return -1;
}

int fileloader(const char filename, user **ptr)
{
    int i = 0;
    char buffer[40];
    int bufferi;
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("error opning file for loading");
        return -1;
    }
    while (fscanf(filename, "%s", buffer) != 0)
    {

        i++;
    }
    *ptr = (user *)malloc(i * sizeof(user));
    i = 0;
    if (strcmp(filename, "users.txt") == 0)
    {
        while (fscanf(filename, "%s", buffer) != 0)
        {
            strcpy((*ptr + i)->username, buffer);
            i++;
        }
    }
    if (strcmp(filename, "passwords.txt") == 0)
    {
        while (fscanf(filename, "%s", buffer) != 0)
        {
            strcpy((*ptr + i)->password, buffer);
            i++;
        }
    }
    if (strcmp(filename, "scores.txt") == 0)
    {

        while (fscanf(filename, "%d", bufferi) != 0)
        {
            strcpy((*ptr + i)->score, bufferi);
            i++;
        }
    }
    return 1;
}

void main()
{

    int *result = (int *)malloc(sizeof(int));
    int *secsesif = (int *)malloc(sizeof(int));
    int questionline = 0;
    user users[MAXUSERS];
    user* p;
    
    char username[40], password[40];
    int id;
    char answer[500], valuetoD[500], newvalue[500];
    int starttime = time(NULL);
    int targetT = starttime + 60;
    const char filename[20];
    char tempfilename[20];

    char choice;

    greeting();
    fileloader("users.txt", p);
    fileloader("passwords.txt", p);
    fileloader("scores.txt", p);
    scanf(" %c", &choice);
    if (choice == 'n')
    {
        printf("enter username");

        signup(p, &username, &password);
    }
    else if (choice == '\n')
    {
        int s = loginusingstruct(p, userid(p, username));
        if (1 == s)
        {
            bool resume = 1;

            do
            {
                choice = '\0';

                printf(" **A,D to add,delete user** || **Q,W to add,delete a question** || **a,b to add,delete answer** || X to exit \n P to print a file || E to edit a file \n  > ");
                scanf(" %c", &choice);

                switch (choice)
                {
                case 'X':
                    exit(0);

                case 'A':
                    id = findidforenw(p);
                    printf("enter username");
                    scanf("%s", username);
                    printf("enter a password");
                    scanf("%s", password);
                    addinstruct(p,id,&password,&username);
                    break;

                case 'E':

                    printf("please enter the file name :\n>");
                    scanf(" %s", tempfilename);
                    strcpy((char *)(filename), tempfilename);
                    printf("please enter the value you want to edit :\n>");
                    scanf(" %s", valuetoD);
                    printf("please enter the new value : \n>");
                    scanf(" %s", newvalue);
                    edit(filename, valuetoD, newvalue);
                    break;

                case 'Q':

                    break;

                case 'W':

                    break;

                case 'a':

                    break;

                case 'b':

                    break;

                case 'D':

                    printf("please enter the username of the user you want to delete:\n>");
                    scanf("%s", username);
                    deletee("users.txt", username);
                    userpassdeleter(username);
                    break;

                case 'P':
                    printf("please enter the file name you want to print");
                    scanf(" %s", tempfilename);
                    strcpy((char *)(filename), tempfilename);

                    printer(filename);
                    break;

                default:
                    break;
                }
            } while (resume);
        }
        else if (s == 3)
        {
            questionline = quizing(username);
            scanf(" %s", answer);
            while (targetT > starttime)
            {
                int remaning = targetT - time(NULL);
                printf("%d", remaning);
                fflush(stdout);
                sleep(1);
            }
            scorcaculator(chekanswer(answer, questionline), result, secsesif);
        }
    }
    free(result);
    free(secsesif);
}
