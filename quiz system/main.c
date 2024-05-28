#include <stdio.h>
#include <strings.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int MAXUSERS=1000;

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

int checker(char u[], const char filename[])
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
int findlinenumber(char valuetochek[], const char filename[])
{

    int linenumber = 1;
    char tempval[300];

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("error opning file");
        return -1;
    }

    while (fscanf(file, "%s", tempval) != 0)
    {

        if (tempval == valuetochek)
        {

            return linenumber;
        }
        linenumber++;
    }
    return -1;
}
int spisifiedlinecheck(char tochek[], int lineN, const char filename[])
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
int usernamevalidation(user *p, char username[])
{
    for (int i = 0; i < MAXUSERS; i++)
    {
        if (strcasecmp((p + i)->username, username) == 0)
        {
            return 1;
            break;
        }
    }

    return 0;
}
int passwordvalidation(char p[])
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

        if (isupper(*(p + i)))
        {
            hasspecialcharacter = true;
        }
        if (islower(*(p + i)))
        {
            haslowercharcter = true;
        }
        if (isdigit(*(p + i)))
        {
            hasnumber = true;
        }
        if (ispunct(*(p + i)))
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
int addinstruct(user *p, int id, char password[], char username[])
{

    if (!usernamevalidation(p, username))
    {
        do
        {
            printf("please enter a valid username");
            scanf("%s", username);

        } while (!usernamevalidation(p, username));
    }
    else
    {

        strcpy((p + id)->username, username);
    }

    printf("enter password");
    scanf("%s", password);

    if (!passwordvalidation(password))
    {
        do
        {
            printf("please enter a valid password");
            scanf("%s", password);

        } while (!passwordvalidation(password));
    }
    else
    {

        strcpy((p + id)->password, password);
    }

    return 1;
}
int login(user *p, char username[], char password[])
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
            fscanf(fpp, "%s", password);

            Uline = findlinenumber(password, "passwords");
            if (strcasecmp(password, tempp) == 0 && Uline != -1)
            {
                printf("welcome admin\n");
                strcpy(username, tempu);
                return 1;
            }
            else
            {
                printf("wrong password try again (%d tryes left) please:\n>", 4 - tryes);
                tryes++;
            }
        } while (strcasecmp(password, tempp) != 0 && tryes < 4);
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
                    strcpy(username, tempu);
                    return 2;
                }
                else
                {
                    printf("wrong password try again (%d tryes left) please:\n>", 4 - tryes);
                    tryes++;
                }
            } while (strcasecmp(password, tempp) != 0 && tryes < 4);
        }
    }
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
int signup(user *ptr, char u[], char p[])
{
    int tryes = 4;

    printf("please enter your username");
    scanf("%s", u);
    if (checker(u, "users.txt") == 0)
    {
        FILE *fileu = fopen("users.txt", "a+");
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

        FILE *fileu = fopen("users.txt", "a+");
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
            }
            else
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
            scanf("%s", p);
        } while (!passwordvalidation(p));
    }

    addinstruct(ptr, findidforenw(ptr), p, u);
}
int deletee(const char filename[], char valuetoD[])
{
    const char tempfile[15];
    char readingtemp[50];

    strcpy((char *)tempfile, filename);
    strcat((char *)tempfile, "tempC");
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen(tempfile, "w");
    if (file == NULL || temp == NULL)
    {
        printf("error opning a file ");
        return -1;
    }
    else
    {
        while (fscanf(file, "%s", readingtemp) != 0)
        {
            if (strcasecmp(readingtemp, valuetoD) == 0)
            {
                continue;
            }
            else
            {
                fprintf(temp, "%s\n", readingtemp);
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
int edit(const char filename[], char valuetoD[], char newvalue[])
{

    const char tempfile[15];
    char readingtemp[500];

    strcpy((char *)tempfile, filename);
    strcat((char *)tempfile, "tempC");
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen(tempfile, "w");
    if (file == NULL || temp == NULL)
    {
        printf("error opning a file ");
        return -1;
    }
    else
    {
        while (fscanf(file, "%s", readingtemp) != 0)
        {
            if (strcasecmp(readingtemp, valuetoD) == 0)
            {
                fprintf(temp, "%s", newvalue);
            }
            else
            {
                fprintf(temp, "%s\n", readingtemp);
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
int howmanyline(const char filename[])
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

    while (fscanf(file, "%s", tempQ) != 0)
    {

        if (linenumber == line)
        {
            printf("YOUR QUESTION IS : %s", tempQ);
            break;
        }
        linenumber++;
    }
    return linenumber;
}
int chekanswer(char answer[], int Qlinenumber)
{
    FILE *file = fopen("aswers", "r");
    if (file == NULL)
    {
        printf("error opning a file ");
        return -1;
    }
    char rightA[500], tempA[500];

    int linenumber = 1;
    while (fscanf(file, "%s", tempA))
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
int userpassdeleter(char u[])
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
    char buffer[50];
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("error opning file ");
    }

    while (fscanf(file, "%s", buffer) != 0)
    {
        fprintf(stdout, "%s", buffer);
    }
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
void deleteuserS(user *p, int id)
{
    if ((p + id)->id != 0)
    {
        (p + id)->id = 0;
        strcpy((p + id)->username, "0");
        strcpy((p + id)->password, "0");
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
        if (strcasecmp(stemp, (char *)'\n') != 0)
        {

            scanf("%s", (p + id)->username);
        }
        printf("Enter new password: ");
        scanf("%s", stemp);
        if (strcasecmp(stemp, (char *)'\n') != 0)
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
int userid(user *p, char username[], int maxusers)
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
int fileloader(const char filename[], user **ptr, int *currentsize)
{
    int i = 0;
    char buffer[40];
    int bufferi = 0;
    FILE *fp = fopen("users.txt", "r");
    while (fscanf(fp, "%s", buffer) != 0)
    {

        i++;
    }
    *currentsize += i;
    rewind(fp);
    *ptr = (user *)realloc(&ptr, *currentsize * sizeof(user));

    i = 0;
    if (strcmp((char *)filename, (char *)"users.txt") == 0)
    {
        FILE *file = fopen("users.txt", "r");

        if (file == NULL)
        {
            printf("error opning file for loading");
            return -1;
        }

        while (fscanf(file, "%s", buffer) != 0)
        {
            strcpy((*ptr + i)->username, buffer);
            i++;
        }
        fclose(file);
    }
    if (strcmp(filename, "passwords.txt") == 0)
    {
        FILE *file = fopen("passwords.txt", "r");
        if (file == NULL)
        {
            printf("error opning file for loading");
            return -1;
        }
        while (fscanf(file, "%s", buffer) != 0)
        {

            i++;
        }
        rewind(file);
        *ptr = (user *)realloc(&ptr, *currentsize * sizeof(user));
        while (fscanf(file, "%s", buffer) != 0)
        {
            strcpy((*ptr + i)->password, buffer);
            i++;
        }
        fclose(file);
    }
    if (strcmp(filename, "scores.txt") == 0)
    {
        FILE *file = fopen("scores.txt", "r");
        if (file == NULL)
        {
            printf("error opning file for loading");
            return -1;
        }
        while (fscanf(file, "%d", &bufferi) != 0)
        {
            (*ptr + i)->score = bufferi;
            i++;
        }
        fclose(file);
    }
    return 1;
}
int loginstructv2(user *ptr, char username[], char password[], int MAXUSERS)
{
    int i = 0;
    while (i < MAXUSERS)
    {
        if (strcmp((ptr + i)->username, username) == 0)
        {
            if (strcmp((ptr + i)->password, password) == 0)
            {
                return 1;
            }
            printf("user name deosnot exist");
            return -1;
        }
    }
}

void main()
{
    int *result = (int *)malloc(sizeof(int));
    int *secsesif = (int *)malloc(sizeof(int));
    int questionline = 0;
    user users[MAXUSERS];
    user *p = users; // Directly initialize p to the users array

    char username[40], password[40];
    int id;
    char answer[500], valuetoD[500], newvalue[500];
    int starttime = time(NULL);
    int targetT = starttime + 60;
    const char filename[20];
    char tempfilename[20];

    char choice;

    greeting();
    fileloader("users.txt", &p, &MAXUSERS);
    fileloader("passwords.txt", &p, &MAXUSERS);
    fileloader("scores.txt", &p, &MAXUSERS);

    scanf("%c", &choice);
    if (choice == '\n') // Changed 'n' to '\n' for signup
    {
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        signup(p, username, password); // Pass arrays directly, not pointers
    }
    else if (choice == 'l') // Changed '\n' to 'l' for login
    {
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        int s = loginstructv2(p, username, password, MAXUSERS);
        // Continue with your login logic...
    }

    free(result);
    free(secsesif);
}
