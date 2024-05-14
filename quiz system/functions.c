#include"functions.h"
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

int signup(user *pp)
{
    char u[40], p[40];
    printf("please enter your username");
    scanf("%s", &u);
    do
    {
        printf("please enter a valid username \n>");
        scanf("%s", &u);

    } while (checker(u) != 0);
    FILE *fileu = fopen("user.txt", "a+");
    if (file == NULL)
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
    structwriter(pp, howmanyline(users), "user", u);
    printf("please enter your password");
    scanf("%s", &p);
    do
    {
        printf("please try again and try with valid password\n>");
        scanf("%s", &p);
    } while (!passwordvalidation(p));
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

    structwriter(pp, howmanyline(passwords), "password", p);
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
        return i;
    }
    else
    {
        printf("value not found");
        return 0;
    }
}


    int structwriter(user *p, int id, const char atribut[10], union Value)
    {
        
        if (strcmp(atribut, "id") == 0 || strcmp(atribut, "score") == 0)
        {
            return write_int_to_struct(p, id, atribut, value.int_value);
        }
        else if (strcmp(atribut, "username") == 0 || strcmp(atribut, "password") == 0)
        {
            return write_string_to_struct(p, id, atribut, value.string_value);
        }
        else
        {
            printf("Invalid attribute\n");
            return -1;
        }
    }

    


int write_int_to_struct(user *p, int id, const char atribut[10], int value)
{
    if (strcmp(atribut, "id") == 0)
    {
        p[id].id = value;
    }
    else if (strcmp(atribut, "score") == 0)
    {
        p[id].score = value;
    }
    else
    {
        printf("Invalid attribute for write_int_to_struct\n");
        return -1;
    }

   
    char filename[50];                      
    strncpy(filename, atribut);
              
    strcat(filename, ".txt");

    FILE *fp = fopen(filename, "a+");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return -1;
    }

    fprintf(fp, "%d\n", value); 

    fclose(fp);
    return 1;
}


int write_string_to_struct(user *p, int id, const char atribut[10], char value[50])
{
    if (strcmp(atribut, "username") == 0)
    {
        strcpy(p[id].username, value);
    }
    else if (strcmp(atribut, "password") == 0)
    {
        
        strcpy(p[id].password, value); 
    }
    else
    {
        printf("Invalid attribute for write_string_to_struct\n");
        return -1;
    }

    
    char filename[50];
    strncpy(filename, atribut);
    
    strcat(filename,".txt");

    FILE *fp = fopen(filename, "a+");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return -1;
    }

    fprintf(fp, "%s\n", value);

    fclose(fp);
    return 1;
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

        if (isupper(p[i]))
        {
            hasspecialcharacter = true;
        }
        if (islower(p[i]))
        {
            haslowercharcter = true;
        }
        if (isdigit(p[i]))
        {
            hasnumber = true;
        }
        if (ispunct(p[i]))
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
int loginusingstruct(user *pn)
{
    char u[40], p[40];
    int tryes = 0;
    printf("please enter your user name \n>");
    scanf("%s", u);
    do
    {
        printf("please enter valide username \n>");
        scanf("%s", u);
        tryes++;
        if (tryes == 5)
        {
            exit();
        }
        else
        {
            printf("you have %d of tryes before the program exit ", 5 - tryes);
        }

    } while (checker(u) != 0 && checker(u) != -1);
    if (strcmp(u, "admin") == 0)
    {
        printf("welcom back admin please enter your password to authenticate");
        scanf("%s", p);
        do
        {
            scanf("%s", p);
            if (pn[0]->password == p[0] && pn[0]->username == u)
            {
                return 1;
            }
            else
            {
                printf("authentication problem retry typing password remain tryies %d", tryes);
                return 0;
            }
            tryes++;
        } while (tryes < 4);
    }

    int tryes = 0, id = structvalexistance(pn, "users.txt", u);
    printf("now please enter your password");
    scanf("%s", p);
    do
    {
        scanf("%s", p);
        if (pn[id]->password == p[id] && pn[id]->username == u)
        {
            return 3;
        }
        else
        {
            printf("authentication problem retry typing password remain tryies %d", tryes);
            return 2;
        }
        tryes++;
    } while (tryes < 4);
}


