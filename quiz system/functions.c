#include <stdio.h>
#include <stdio.h>
#include <strings.h>
#include <time.h>
#include <stdbool.h>

int greeting()
{

    printf("################## Hello, welcome to the Quizing system ######################\n press enter to sing up else \n 'A' to authentecate ");
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

        FILE *fpp = fopen("passwords.txt", "r");

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
        if (Uline = checker(u, "users.txt") != 0)
        {

            printf("Now please type the password: \n>");

            FILE *fpp = fopen("passwords.txt", "r");
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

int signup()
{

    char u[32], p[32];
    printf("Welcome to singup please start with typing your username: \n>");
    fgets(u, sizeof(u, stdin));

    if (checker(u, "users.txt") != 0)
    {
        printf("Now please type your password: \n>");
        fgets(p, sizeof(p, stdin));
        FILE *fpu = fopen("users.txt", "a");
        FILE *fpp = fopen("passwords.txt", "a");

        if (fpu == NULL || fpp == NULL)
        {
            printf("eroor singing up");
        }
        else
        {
            fprintf(fpu, "%s", u);
            fprintf(fpp, "%s", p);
            fclose(fpu);
            fclose(fpp);
            printf("you are now signed up");
        }
    }
}

int deletefrom(const char filename[15], char valuetoD[])
{

    FILE *file = fopen(filename, "")
}