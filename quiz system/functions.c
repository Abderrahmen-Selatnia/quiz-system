#include<stdio.h>
#include <stdio.h>
#include <strings.h>
#include <time.h>
#include <openssl/sha.h>

int greeting()
{

    printf("################## Hello, welcome to the Quizing system ######################\n press enter to sing up else \n 'A' to authentecate ");

}

int login(){

}

int checker(char u[30])
{
    int linenumber =1;
    FILE *file;
    char tempcmpusername[30];
    file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("could not check the username pro");
    }
    while (fgets(tempcmpusername, sizeof(tempcmpusername), file) != NULL) // to read the file by lines untill nULL , not by chars i use fgets
    {
        char *result = strstr(tempcmpusername, u); // comparing usign strstr storing the result in result var then compair with null the function return 1 if it found it
        if (result != NULL)
        {
           
            return linenumber;
            break;
           
        }
        else
        {
            linenumber ++;
            return 0
        }
        
    }
    fclose(file);
    
}

int singup(char *file,  char u[31],char *file2, char p[34])
{
    FILE *file = fopen(file, "a");
    FILE *file2 = fopen(file2, "a");
    if (file == NULL)
    {
        printf("Error opening %s!\n",file);

        exit();
    }
    if (file2 == NULL)
    {
        printf("Error opening %s!\n", file2);

        exit();
    }
    fputs(u, file);
    fputs(p, file2);
    fclose(file);
}


int 