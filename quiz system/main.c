#include<stdio.h>
#include<strings.h>
#include<time.h>
#include<openssl/sha.h>
#include"functions.h"







int login (char username[],char password[]){


//** we need to pars the file of pass and users to authenticate return 1  if correct else 0 ***//
    
}

void signup(){

{
    
    
}





}


int main(){

char username[30];
char password[34];
char LoGINchoice[34];
int eror;

greeting();
do
{
    /* code */
} while (/* condition */);

fgets(LoGINchoice,sizeof(LoGINchoice),stdin);
printf("\n");
if (LoGINchoice=='\n'){
    printf("\nEnter a Username: ");
    fgets(username, 100, stdin);

    if (checker(username))
    {
        printf("user name already exist");
        
        
    }else
    {
        printf("Username accepted\nplease enter a password now : \n");
        fgets(password, sizeof(password), stdin);
        signup("users.text",username,"psaswords.text",password);
    }
    

    printf("\nEnter a Password (it must has both cases of chars and at least a symbol and number max leght is 33 char ):");
    fgets(password, 100, stdin);
    login(username, password);

    append_to
    


}else if (LoGINchoice=='A')
{
    printf("\nEnter a Username: ");
    fgets(username, 100, stdin);
    if (checker(username))
    {
        printf("please enter your password  to continue:\n");
        fgets(password, sizeof(password), stdin);
        login(username,password);
        if(username=="admin" && login==1){



        }
    }
    else
    {
        printf("user deos not exist please try agin  or create an acount ");
    }
}


