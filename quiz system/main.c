#include <stdio.h>
#include <strings.h>
#include <time.h>
#include <openssl/sha.h>
#include "functions.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>
#define MAXUSERS 1000

void main()
{

    typedef struct user{
        char username[32];
        char password[32];
        int scoor;
        int id;
    };

    typedef union Value
    {
        int int_value;
        char string_value[50];
    }value;

    int*result = (int*)malloc(sizeof(int));
    int *secsesif = (int *)malloc(sizeof(int));
    int questionline =0 ;
    user users[MAXUSERS];
    user *upoint;
    upoint=users;
    char username[40], password[40];
    char answer[500], valuetoD[500], newvalue[500];
    int starttime = time(NULL);
    int targetT = starttime + 60;
    const char filename[20];
    char tempfilename[20];

    char choice;

    greeting();
    scanf(" %c",&choice);
    if (choice == 'n')
    {
        signup(upoint);
    }
    else if (choice == '\n')
    {
        int s = loginusingstruct(upoint);
        if (1 == s)
        {
            bool resume = 1;

            do
            {
                choice ='\0';

                printf(" **A,D to add,delete user** || **Q,W to add,delete a question** || **a,b to add,delete answer** || X to exit \n P to print a file || E to edit a file \n  > ");
                scanf(" %c", &choice);

                switch (choice)
                {
                case 'X':
                    exit(0);

                case 'A':
                    signup(upoint);
                    break;

                case 'E':

                    printf("please enter the file name :\n>");
                    scanf(" %s", tempfilename);
                    strcpy((char *)(filename), tempfilename);
                    printf("please enter the value you want to edit :\n>");
                    scanf(" %s",valuetoD);
                    printf("please enter the new value : \n>");
                    scanf(" %s",newvalue);
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
                    delete ("users.txt", username);
                    userpassdeleter(username);
                    break;

                case 'P':
                    printf("please enter the file name you want to print");
                    scanf(" %s",tempfilename);
                    strcpy((char *)(filename),tempfilename);

                    printer(filename);
                    break;

                default:
                    break;
                }
            } while (resume);
        }
        else if (s == 3)
        {
            questionline =quizing(username);
            scanf(" %s", answer);
            while (targetT > starttime)
            {
                int remaning = targetT - time(NULL);
                printf("%d", remaning);
                fflush(stdout);
                sleep(1);
            }
            scorcaculator(chekanswer(answer,questionline), result,secsesif);
        }
    }
    free(result);
    free(secsesif);
}



