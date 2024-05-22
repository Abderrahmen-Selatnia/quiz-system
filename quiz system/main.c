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
    else if((10 - *secsesif) == 4)
    {
        printf("%d one after another you are the best \n>", 10 - *secsesif);
    }
    else if(10 - *secsesif == 0)
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
            delete ("paswwords.txt", temppass);
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

        if (isupper((p+i)))
        {
            hasspecialcharacter = true;
        }
        if (islower((p+i)))
        {
            haslowercharcter = true;
        }
        if (isdigit((p+i)))
        {
            hasnumber = true;
        }
        if (ispunct((p+i)))
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

        if (strcmp((p+id)->password, password) == 0)
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
    printf("enter username");
    scanf("%s",*username);
    if (!usernamevalidation(*username))
    {
        do
        {
            printf("please enter a valid username");
            scanf("%s",*username);

        } while (!usernamevalidation(*username));
    }
    else
    {

        strcpy((p + id)->username, *username);
    }

    printf("enter password");
    scanf("%s", *password);

    if (!passwordvalidation(*password))
    {
        do
        {
            printf("please enter a valid password");
            scanf("%s", *password);

        } while (!passwordvalidation(*password));
    }
    else
    {

        strcpy((p + id)->password, *password);
    }

    return 1;
}
int findidforenw(user *p)
{

    for (int i = 0; i < MAXUSERS; i++)
    {
        if ((p+i)->id = 0)
        {
            return i;
        }
    }
}
int usernamevalidation(user *p,char *username)
{
    for (int i = 0; i < MAXUSERS; i++)
    {
        if (strcasecmp((p+i)->username, *username) == 0)
        {
            return 1;
            break;
        }
    }

    return 0;
}
void deleteuserS(user *p, int id)
{
    if ((p+id)->id != 0)
    {
        (p+id)->id= 0;
        strcpy((p + id)->username,'0');
        strcpy((p + id)->password,'0');
        (p+id)->score = 0;
        printf("User deleted successfully.\n");
    }
    else
    {
        printf("User with ID %d not found.\n", id);
    }
}
void edituserS(user *p, int id)
{
    if ((p+id)->id != 0)
    {

        char stemp[50];
        printf("Enter new username: ");
        scanf("%s", stemp);
        if (strcasecmp(stemp, '\n') != 0)
        {
       
        
            scanf("%s", (p+id)->username);
        }
        printf("Enter new password: ");
        scanf("%s", stemp);
        if (strcasecmp(stemp, '\n') != 0)
        {
         
            scanf("%s", (p+id)->password);
        }

        printf("User details updated successfully.\n");
    }
    else
    {
        printf("User with ID %d not found.\n", id);
    }
}
int userid(user *p,char username[])
{
    for (int i = 0; i < MAXUSERS; i++)
    {
        if (strcmp((p+i)->username, username) == 0)
        {
            return i;
        }
    }
    return -1;
}

void main()
{

   
 

    int *result = (int *)malloc(sizeof(int));
    int *secsesif = (int *)malloc(sizeof(int));
    int questionline = 0;
    user users[MAXUSERS];
    user *p;
    p = &users;
    char username[40], password[40];
    int id;
    char answer[500], valuetoD[500], newvalue[500];
    int starttime = time(NULL);
    int targetT = starttime + 60;
    const char filename[20];
    char tempfilename[20];

    char choice;

    greeting();
    scanf(" %c", &choice);
    if (choice == 'n')
    {
        printf("enter username");
        scanf("%s",username);
        addinstruct(p,userid(username,&id),&password,&username);
    }
    else if (choice == '\n')
    {
        int s = loginusingstruct(p,userid(p,username));
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
                    id=findidforenw(p);
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
                    delete("users.txt",username);
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
