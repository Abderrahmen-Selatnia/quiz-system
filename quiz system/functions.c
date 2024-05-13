#include <stdio.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

int greeting()
{

    printf("################## Hello, welcome to the Quizing system ######################\n press enter to sing in else \n 'n' to sing up ");
}

int login()
{
    int Uline, tryes = 1;
    char u[32], p[32], temppass[30];
    printf("please enter your username: \n>");
    fgets(u, sizeof(u), stdin);
    if (strcmp("admin", u) == 0)
    {
        printf("Now please type the password: \n>");

        FILE *fpp = fopen("password.txt", "r");

        if (fpp == NULL)
        {
            printf("could not open file ");
            return -1;
        }
        fscanf(fpp, "%s", &temppass);
        do
        {
            fgets(p, sizeof(p), stdin);
            if (strcasecmp(p, temppass) == 0)
            {
                printf("welcome admin\n");
                fgets(&username, sizeof(username), u);
                return 1;
            }
            else
            {
                printf("wrong password try again (%d tryes left) please:\n>", 4 - tryes);
                tryes++;
            }
        } while (strcasecmp(p, temppass) != 0 && tryes < 4);
    }
    else
    {
        if (checker(u, "users.txt") != 0)
        {
            Uline = checker(u, "users.txt");
            printf("Now please type the password: \n>");

            FILE *fpp = fopen("password.txt", "r");
            if (fpp == NULL)
            {
                printf("could not open file ");
                return -1;
            }

            do
            {
                fgets(p, sizeof(p), stdin);
                if (linecheck(p, Uline, "paswords.txt"))
                {
                    printf("welcome");
                    fgets(&username, sizeof(username), u);
                    return 2;
                }
                else
                {
                    printf("wrong password try again (%d tryes left) please:\n>", 4 - tryes);
                    tryes++;
                }
            } while (strcasecmp(p, temppass) != 0 && tryes < 4);
        }
    }
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
    while (fscanf(file, "%s", &tempcmpusername) != 0)
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

int linecheck(char tochek[50], int lineN, const char filename[])
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

int signup(int i)
{

    char u[32], p[32];
    if (i = 2)
    {
        printf("Welcome to singup please start with typing your username: \n>");
    }
    else
    {
        printf("please enter the username: \n>");
    }

    fgets(u, sizeof(u, stdin));

    if (checker(u, "users.txt") != 0)
    {
        if (i = 2)
        {
            printf("now please type your pasword: \n>");
        }
        else
        {
            printf("please enter the acount password: \n>");
        }
        fgets(p, sizeof(p), stdin);
        FILE *fpu = fopen("users.txt", "a");
        FILE *fpp = fopen("password.txt", "a");

        if (fpu == NULL || fpp == NULL)
        {
            printf("eroor singing up");
        }
        else
        {
            fprintf(&username, "%s", u);
            fprintf(&password, "%s", p);
            fprintf(fpu, "%s", u);
            int j = 0;
            while (1)
            {
                if (strlen(students[j].username) == 0)
                {
                    strcpy(students[j].username, &username);
                    break;
                }
                else
                {
                    j++;
                }
            }

            fprintf(fpp, "%s", p);
            j = 0;
            while (1)
            {
                if (strlen(students[j].password) == 0)
                {
                    strcpy(students[j].password, &password);
                    break;
                }
                else
                {
                    j++;
                }
            }

            fclose(fpu);
            fclose(fpp);
            if (i = 2)
            {
                printf("Welcome your singedup: \n>");
            }
            else
            {
                printf("the user added secsefully: \n>");
            }
        }
    }
}

int delete(const char filename[15], char valuetoD[])
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
        result -= secsesif;
        secsesif = 0;
        printf("that is not the right way son \n");
    }
    else
    {
        result++;
        secsesif++;
    }
    if (10 - secsesif == 7)
    {
        printf("i like your spirit \n>");
    }
    elsif(10 - secsesif == 4)
    {
        printf("%d one after another you are the best \n>", 10 - secsesif);
    }
    elseif(10 - secsesif == 0)
    {
        printf("respect +  you are a nerd \n");
    }

    result += secsesif;
    return result;
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
        fprintf(file, "%s\n", stdout);
    }
}

int structvalexistance(user *p, const char atribut[10], char scanedvalue[40])
{
    int i = 0;
    bool found == false;
    for (i = 0; i < maxusers; i++)
    {
        if (p[i]->atribut == scanedvalue)
        {
            found == true;
        }
    }
    if (found)
    {
        return 1;
    }
    else
    {
        printf("value not found");
        return 0;
    }
}

int structwriter(s *p, int id, const char atribut[10], void value)
{
    int linenumber = 0;
    char filename[20];
    strcpy(filename, atribut);
    strcat(filename, ".txt");
    if (strcmp(atribut, "id") == 0)
    {
        write_int(s, id, "id", *(int *)value);
    }
    else if (strcmp(atribut, "scoor") == 0)
    {
        write_int(s, id, "scoor", *(int *)value);
    }
    else if (strcmp(atribut, "username") == 0)
    {
        write_string(s, id, "username", *(char **)value);
        FILE *fp = fopen(filename, "a+");
        if (fp == NULL)
        {
            printf("Error opening file\n");
            return -1;
        }
        else
        {

            while (fscanf(fp, "%s", NULL) != EOF)
            {
                linenumber++;
                if (linenumber == id)
                {
                    fprintf(fp, "%s", *(char **)value);
                    fclose(fp);
                    return 1;
                }
            }
        }
    }
    else if (strcmp(atribut, "password") == 0)
    {

        write_string(s, id, "password", *(char **)value);
        FILE *fp = fopen(filename, "a+");
        if (fp == NULL)
        {
            printf("Error opening file\n");
            return -1;
        }
        else
        {

            while (fscanf(fp, "%s", NULL) != EOF)
            {
                linenumber++;
                if (linenumber == id)
                {
                    fprintf(fp, "%s", *(char **)value);
                    fclose(fp);
                    return 1;
                }
            }
        }
    }
    else
    {
        printf("Invalid attribute\n");
    }
    return 0;
}

int write_int(s *p, int id, const char atribut[10], int value)
{

    p[id]->atribut = value;
}

int write_string(s *p, int id, const char atribut[10], char value[50])
{

    p[id]->atribut = value;
}