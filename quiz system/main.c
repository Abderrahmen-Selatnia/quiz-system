#include <stdio.h>
#include <strings.h>
#include <time.h>
#include <openssl/sha.h>
#include "functions.h"
#include <stdbool.h>
#include <ctype.h>
#define maxusers = 1000;

int main(){

    typedef struct
    {
        char username[32];
        char password[32];
        int scoor;
        int id;
    } user;

    user users[1000];
    user *upoint;
    upoint = users;
    char username[40], password[40];
    char answer[500], valuetoD[500], newvalue[500];
    int starttime = time(NULL);
    int targetT = starttime + 60;
    const char filename[20];
    strcpy(username, users[0].username);
    char choice;

    greeting();
    fgets(choice, sizeof(choice), stdin);
    if (choice == 'n')
    {
        singup();
    }
    else if (choice == '\n')
    {
        int s = loginusingstruct(upoint);
        if (1 == s)
        {
            bool resume = true;

            do
            {
                choice == NULL;

                printf("**A,D to add,delete user** || **Q,W to add,delete a question** || **a,b to add,delete answer** || X to exit \n P to print a file || E to edit a file \n>"); // X toexit
                fgets(choice, sizeof(choice), stdin);

                switch(choice)
                {
                case 'X':
                    exit(0);

                case 'A':
                    singup(1);
                    break;

                case 'E':

                    printf("please enter the file name :\n>");
                    scanf("%s",&filename);
                    printf("please enter the value you want to edit :\n>");
                    scanf("%s",&valuetoD);
                    printf("please enter the new value : \n>");
                    scanf("%s",&newvalue);
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
                    scanf("%d", username);
                    delete ("users.txt", username);
                    userpassdeleter(username);
                    break;

                case 'P':
                    printf("please enter the file name you want to print");
                    scanf("%s", filename);
                    printer(filename);
                    break;

                default:
                    break;
                }
            } while (resume);
        }
        elesif(s == 3)
        {

            quizing();
            scanf("%s", answer);
            while (targetT > starttime)
            {
                int remaning = targetT - time(NULL);
                printf("%d", remaning);
                fflush(stdout);
                sleep(1);
            }
            scorcaculator(chekanswer(answer));
        }
    }
    retrun 0;
}