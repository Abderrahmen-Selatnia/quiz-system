#include <stdio.h>
#include <strings.h>
#include <time.h>
#include <openssl/sha.h>
#include "functions.h"
#include <stdbool.h>

int main()
{

    char *username[40];
    char answer[500], valuetoD[500], newvalue[500];
    int starttime = time(NULL);
    int targetT = starttime + 60;
    const char filename[20];

    char choice;
    greeting();
    fgets(choice, sizeof(choice), stdin);
    if (choice == 'n')
    {
        singup();
    }
    else if (choice == '\n')
    {
        int s = login();
        if (1 == s)
        {
            bool resume = true;

            do
            {
                choice == NULL;

                printf("**A,D to add,delete user** || **Q,W to add,delete a question** || **a,b to add,delete answer** || X to exit \n P to print a file || E to edit a file \n>"); // X toexit
                fgets(choice, sizeof(choice), stdin);

                switch (choice)
                {
                case 'X':
                    exit();

                case 'A':
                    singup(1);
                    break;

                case 'E':

                    printf("please enter the file name :\n>");
                    scanf("%s", &filename);
                    printf("please enter the value you want to edit :\n>");
                    scanf("%s", &valuetoD);
                    printf("please enter the new value : \n>");
                    scanf("%s", &newvalue);
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
        elesif(s == 2)
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
            scorcaculator(chekanswer(answer););
        }
    }
}
