#include <stdio.h>
#include <strings.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

int MAXUSERS=1000;
#define MAX_QUESTION_LENGTH 500
#define MAX_ANSWER_LENGTH 500

char answer[MAX_ANSWER_LENGTH];
typedef struct user
{
    char username[32];
    char password[32];
    int score;
    int id;
} user;

void greeting()
{
printf("Press Enter to sign up or 'l' to log in: ");
}


int checker(char u[], const char filename[])
{

    FILE *file;
    char line[30];
    int linenumber = 1;

    file = fopen(filename, "r");
    if (file == NULL)
    {
        // Could not open file
        return -1;
    }

    // Read each line of the file
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Remove newline character if present
        line[strcspn(line, "\n")] = '\0';

        if (strcmp(u, line) == 0)
        {
            // Username found
            fclose(file);
            return linenumber;
        }
        linenumber++;
    }

    // Username not found
    fclose(file);
    return -2;
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
    bool neededlenght = false;
    if (strlen(p) >= 8)
    {

        neededlenght = true;
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
    if (!neededlenght)
    {
        printf("password must be at least 8 characters long\n");
        return 0;
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
    int tries = 4;
    int validUsername = 0; // Flag to track if the username is valid
    int validPassword = 0; // Flag to track if the password is valid

    do
    {
        printf("Please enter your username: ");
        scanf("%s", u);

        if (checker(u, "users.txt") != -2)
        {
            printf("Username is already taken.\n");
            tries--;
            if (tries == 0)
            {
                printf("You've exceeded the maximum number of attempts.\n");
                return -1;
            }
        }
        else
        {
            validUsername = 1; // Username is valid, exit the loop
        }
    } while (!validUsername);

    FILE *fileu = fopen("users.txt", "a+");
    if (fileu == NULL)
    {
        printf("Error opening file for writing.\n");
        return -1;
    }

    fprintf(fileu, "%s\n", u);
    fclose(fileu);

    tries = 4; // Reset tries for password validation retries

    do
    {
        printf("Please enter your password: ");
        scanf("%s", p);

        if (!passwordvalidation(p))
        {
            printf("Invalid password. Please try again.\n");
            tries--;
            if (tries == 0)
            {
                printf("You've exceeded the maximum number of attempts.\n");
                return -1;
            }
        }
        else
        {
            validPassword = 1; // Password is valid, exit the loop
        }
    } while (!validPassword);

    // Add other necessary actions here (e.g., saving the password to a file)

    return 1;
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
    int lines = 0;
    char ch;
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return -1;
    }

    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            lines++;
        }
    }

    fclose(file);
    return lines;
}

void stopwatch(int minutes)
{
    int seconds = minutes * 60;
    while (seconds > 0)
    {
        printf("\r                                           Time remaining: %02d:%02d", seconds / 60, seconds % 60);
        fflush(stdout);
        sleep(1);
        seconds--;
    }
    printf("\rTime is up! \n");
}

int scoreCalculator(char answer, int *result, int *successive, int usernameLine)
{
    if (answer == 'Y' || answer == 'y')
    {
        *result += 1;     // Increment score for correct answer
        *successive += 1; // Increment successive counter
        printf("Correct answer!\n");

        // Check for successive bonus
        if (*successive == 3)
        {
            *result += 5; // Apply a bonus for answering 3 questions correctly in a row
            printf("Three in a row! Bonus points added.\n");
        }
    }
    else
    {
        *successive = 0; // Reset successive bonus if answer is incorrect
        printf("Incorrect answer.\n");
    }

    // Store the score in scores.txt at the same line number as the username
    FILE *scoresFile = fopen("scores.txt", "r+");
    if (scoresFile == NULL)
    {
        printf("Error opening scores file.\n");
        return -1;
    }

    fseek(scoresFile, (usernameLine - 1) * sizeof(int), SEEK_SET); // Move to the appropriate line in scores.txt
    fwrite(result, sizeof(int), 1, scoresFile);                    // Write the score to scores.txt
    fclose(scoresFile);

    return *result;
}

int checkAnswer(const char userAnswer[], int questionLineNumber)
{
    FILE *file = fopen("answers.txt", "r");
    if (file == NULL)
    {
        printf("Error opening answers file.\n");
        return -1;
    }

    char correctAnswer[MAX_ANSWER_LENGTH];
    int currentLineNumber = 1;
    while (fgets(correctAnswer, sizeof(correctAnswer), file) != NULL)
    {
        if (currentLineNumber == questionLineNumber)
        {
            // Remove newline character from correctAnswer
            correctAnswer[strcspn(correctAnswer, "\n")] = '\0';
            if (strcmp(correctAnswer, userAnswer) == 0)
            {
                printf("Correct answer!\n");
                fclose(file);
                return 1;
            }
            else
            {
                printf("Wrong answer. The correct answer is: %s\n", correctAnswer);
                fclose(file);
                return 0;
            }
        }
        currentLineNumber++;
    }

    fclose(file);
    printf("Answer not found.\n");
    return -1;
}

void quizing(char username[])
{
    int totalLines = howmanyline("questions.txt");
    if (totalLines <= 0)
    {
        printf("Error reading file or file is empty.\n");
        return;
    }

    srand(time(NULL)); // Seed the random number generator
    int numQuestions;
    printf("How many questions would you like to answer? ");
    scanf("%d", &numQuestions);
    if (numQuestions <= 0)
    {
        printf("Invalid number of questions.\n");
        return;
    }

    int result = 0;                                    // Initialize result to track the score
    int successive = 0;                                // Initialize successive to track bonus streak
    int usernameLine = checker(username, "users.txt"); // Get the line number of the username in users.txt

    for (int i = 0; i < numQuestions; i++)
    {
        int line = rand() % totalLines + 1; // Random line number between 1 and totalLines

        char tempQ[MAX_QUESTION_LENGTH];
        int lineNumber = 1;

        FILE *file = fopen("questions.txt", "r");
        if (file == NULL)
        {
            printf("Error opening questions file.\n");
            return;
        }

        // Read questions and display the random one
        while (fgets(tempQ, sizeof(tempQ), file) != NULL)
        {
            if (lineNumber == line)
            {
                // Remove newline character from tempQ
                tempQ[strcspn(tempQ, "\n")] = '\0';
                system("clear");
                printf("Your question is: %s\n", tempQ);
                break;
            }
            lineNumber++;
        }
        fclose(file);

        // Ask for user's answer
        char userAnswer[MAX_ANSWER_LENGTH];
        printf("Your answer: ");
        scanf("%s", userAnswer); // Get the user's answer

        // Check the answer immediately and update the score
        int answerStatus = checkAnswer(userAnswer, line);
        if (answerStatus == 1)
        {
            scoreCalculator('Y', &result, &successive, usernameLine);
        }
        else
        {
            scoreCalculator('N', &result, &successive, usernameLine);
        }
    }

    printf("Quiz completed! Your final score is: %d\n", result);
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
int fileloader(const char filename[], user **ptr, int *maxUsers)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return -1;
    }

    char buffer[64];
    int count = 0;
    int currentMaxUsers = *maxUsers;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        if (count >= currentMaxUsers)
        {
            currentMaxUsers *= 2; // Double the size of the array
            user *tempPtr = realloc(*ptr, currentMaxUsers * sizeof(user));
            if (tempPtr == NULL)
            {
                printf("Memory reallocation failed\n");
                fclose(file);
                return -1;
            }
            *ptr = tempPtr;
            *maxUsers = currentMaxUsers;
        }

        if (strstr(filename, "users"))
        {
            strncpy((*ptr)[count].username, buffer, sizeof((*ptr)[count].username) - 1);
            (*ptr)[count].username[sizeof((*ptr)[count].username) - 1] = '\0'; // Ensure null-terminated
        }
        else if (strstr(filename, "passwords"))
        {
            strncpy((*ptr)[count].password, buffer, sizeof((*ptr)[count].password) - 1);
            (*ptr)[count].password[sizeof((*ptr)[count].password) - 1] = '\0'; // Ensure null-terminated
        }
        else if (strstr(filename, "scores"))
        {
            (*ptr)[count].score = atoi(buffer); // Convert string to integer
        }

        (*ptr)[count].id = count + 1; // Assign unique ID

        count++;
    }

    fclose(file);
    return 0;
}

int loginstructv2(user *ptr, char username[], char password[], int MAXUSERS)
{
    int triesLeft = 4;
    int userExists = 0;
    int id = -1;
    int isAdmin = 0; // Flag to track if admin signed in

    while (triesLeft > 0)
    {
        printf("Please enter username: ");
        scanf("%s",username);

        for (int i = 0; i < MAXUSERS; i++)
        {
            if (strcmp((ptr + i)->username, username) == 0)
            {
                userExists = 1;
                id = i;

                
                if (strcmp(username,"admin") == 0 )
                {
                    printf("Username found. Please enter password: ");
                    scanf("%s", password);
                    if (strcmp((ptr+i)->password, password) == 0)
                    {
                        
                        isAdmin = 1;
                        break;
                    }
                    
                    
                }

                break;
            }
        }

        if (!userExists)
        {
            triesLeft--;
            printf("Username not found. Tries left: %d\n", triesLeft);
            continue;
        }

        if (isAdmin) // Admin signed in
        {
            return 9; // Unique value for admin
        }

        printf("Username found. Please enter password: ");
        scanf("%s", password);

        if (strcmp((ptr + id)->password, password) == 0)
        {
            return 1; // Username and password match
        }
        else
        {
            triesLeft--;
            printf("Invalid password. Tries left: %d\n", triesLeft);
        }
    }

    printf("No more tries left. Exiting...\n");
    return -1;
}



int main()
{
        int result = 0;
        char answer[1000];
        user users[MAXUSERS];
        user *p = users; // Directly initialize p to the users array

        char username[40], password[40];
        char choice;

        greeting();
        fflush(stdin);
        fileloader("users.txt", &p, &MAXUSERS);
        fileloader("passwords.txt", &p, &MAXUSERS);
        fileloader("scores.txt", &p, &MAXUSERS);

        scanf("%c", &choice);
        if (choice == '\n') // Changed 'n' to '\n' for signup
        {
           result = signup(p, username, password); // Pass arrays directly, not pointers
            if (result == 1)
            {
                printf("Sign up successful!\n");
                printf("%s %s %d", (p + 1)->username, (p + 1)->username, (p + 1)->id);
            }
            else
            {
                printf("Sign up failed. Please try again.\n");
            }
        }
        else if (choice == 'l') // Changed '\n' to 'l' for login
        {
           
            int s = loginstructv2(p, username,password, MAXUSERS);
            if (s == 1)
            {
                printf("Login successful!\n");

                quizing(username);
                // Proceed with actions after login...
            }else if (s == 9)
            {
                printf("\n*********welcome admin********\n");
               
            }

            else
            {
                printf("Login failed. Please try again.\n");
            }
        }

        return 0;
 }
