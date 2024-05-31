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
#include<ctype.h>

int MAXUSERS=1000;
#define MAX_QUESTION_LENGTH 500
#define MAX_ANSWER_LENGTH 500
#define MAX_USERNAME_LENGTH 50
#define MAX_ENTRIES 100
char answer[MAX_ANSWER_LENGTH];
#define LEADERBOARD_FILE "leaderboard.txt"

typedef struct
{
    char username[MAX_USERNAME_LENGTH];
    int numQuestions;
    int correctAnswers;
    float finalScore;
} UserScore;

typedef struct user
{
    char username[32];
    char password[32];
    UserScore userScore;
    int id;
} user;
struct LeaderboardEntry
{
    char username[MAX_USERNAME_LENGTH];
    int sessionNumber;
    int totalQuestionsAnswered;
    float score;
    int rank;
}entry;
void greeting()
{
printf("Press Enter to sign up or 'l' to log in: ");
}
user *p;
char username[50], password[50];
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

int login1(user *p, char username[], char password[])
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

    if (validPassword)
    {
        FILE *fileu = fopen("users.txt", "a+");
        if (fileu == NULL)
        {
            printf("Error opening file for writing.\n");
            return -1;
        }

        fprintf(fileu, "%s\n", u);
        fclose(fileu);

        tries = 4; // Reset tries for password validation retries

        FILE *filep = fopen("passwords.txt", "a+");
        if (filep == NULL)
        {
            printf("Error opening file for writing.\n");
            return -1;
        }

        fprintf(filep, "%s\n", p);
        fclose(filep);
    }

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

void trimWhitespace(char *str)
{
    char *start = str;
    char *end;

    // Trim leading whitespace
    while (isspace((unsigned char)*start))
        start++;

    if (*start == 0)
    { // All spaces?
        str[0] = '\0';
        return;
    }

    // Trim trailing whitespace
    end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end))
        end--;

    // Write new null terminator
    *(end + 1) = '\0';

    // Shift trimmed string back to the original pointer
    if (start != str)
    {
        memmove(str, start, (end - start + 2)); // Include null terminator
    }
}

void toLowerCase(char *str)
{
    for (; *str; str++)
    {
        *str = tolower((unsigned char)*str);
    }
}

int checkAnswer(const char userAnswer[], const char correctAnswer[])
{
    char trimmedUserAnswer[MAX_ANSWER_LENGTH];
    strncpy(trimmedUserAnswer, userAnswer, MAX_ANSWER_LENGTH);
    trimmedUserAnswer[MAX_ANSWER_LENGTH - 1] = '\0'; // Ensure null-termination
    trimWhitespace(trimmedUserAnswer);

    char trimmedCorrectAnswer[MAX_ANSWER_LENGTH];
    strncpy(trimmedCorrectAnswer, correctAnswer, MAX_ANSWER_LENGTH);
    trimmedCorrectAnswer[MAX_ANSWER_LENGTH - 1] = '\0'; // Ensure null-termination
    trimWhitespace(trimmedCorrectAnswer);

    // Convert both answers to lowercase for case-insensitive comparison
    toLowerCase(trimmedUserAnswer);
    toLowerCase(trimmedCorrectAnswer);

    return strcmp(trimmedCorrectAnswer, trimmedUserAnswer) == 0;
}

float scoreCalculator(int correctCount, int totalQuestions)
{
    float score = ((float)correctCount / totalQuestions) * 100;
    return score;
}

void updateRankings()
{
    FILE *file = fopen(LEADERBOARD_FILE, "r+");
    if (file == NULL)
    {
        printf("Error opening leaderboard file.\n");
        return;
    }

    struct LeaderboardEntry entries[100]; // Assuming a maximum of 100 entries
    int numEntries = 0;

    // Read entries from the leaderboard file
    while (fscanf(file, "%s %d %d %f %d", entries[numEntries].username, &entries[numEntries].sessionNumber,
                  &entries[numEntries].totalQuestionsAnswered, &entries[numEntries].score, &entries[numEntries].rank) != EOF)
    {
        numEntries++;
    }

    // Calculate rankings based on total questions answered and score
    for (int i = 0; i < numEntries; i++)
    {
        entries[i].rank = 1; // Initialize rank to 1
        for (int j = 0; j < numEntries; j++)
        {
            if (i != j && entries[i].totalQuestionsAnswered < entries[j].totalQuestionsAnswered)
            {
                entries[i].rank++;
            }
            else if (i != j && entries[i].totalQuestionsAnswered == entries[j].totalQuestionsAnswered && entries[i].score < entries[j].score)
            {
                entries[i].rank++;
            }
        }
    }

    // Update the leaderboard file with updated rankings
    rewind(file); // Move file pointer to the beginning
    for (int i = 0; i < numEntries; i++)
    {
        fprintf(file, "%s %d %d %.2f %d\n", entries[i].username, entries[i].sessionNumber,
                entries[i].totalQuestionsAnswered, entries[i].score, entries[i].rank);
    }

    fclose(file);
}

void updateLeaderboard(const char *username, int sessionNumber, int totalQuestions, float score)
{
    FILE *file = fopen(LEADERBOARD_FILE, "a");
    if (file == NULL)
    {
        printf("Error opening leaderboard file.\n");
        return;
    }

    fprintf(file, "%s %d %d %.2f\n", username, sessionNumber, totalQuestions, score);
    fclose(file);
}

void quizUser(const char *username)
{
    int numQuestions;
    system("clear");
    printf("How many questions do you want to answer? ");
    scanf("%d", &numQuestions);
    getchar(); // Consume newline character

    FILE *questionsFile = fopen("questions.txt", "r");
    if (questionsFile == NULL)
    {
        printf("Error opening questions file.\n");
        return;
    }

    FILE *answersFile = fopen("answers.txt", "r");
    if (answersFile == NULL)
    {
        printf("Error opening answers file.\n");
        fclose(questionsFile);
        return;
    }

    char question[MAX_QUESTION_LENGTH];
    char userAnswer[MAX_ANSWER_LENGTH];
    char correctAnswer[MAX_ANSWER_LENGTH];
    int correctCount = 0;

    // Seed random number generator
    srand(time(NULL));

    for (int i = 0; i < numQuestions; i++)
    {
        // Read the question from questions.txt
        if (fgets(question, sizeof(question), questionsFile) == NULL)
        {
            printf("Error reading question.\n");
            fclose(questionsFile);
            fclose(answersFile);
            return;
        }

        // Remove newline character from question
        question[strcspn(question, "\n")] = '\0';
        system("clear");
        printf("Question %d: %s\n", i + 1, question);
        
        printf("Your answer: ");
        scanf(" %[^\n]", userAnswer);

        // Read the correct answer from answers.txt using line number from questions.txt
        if (fgets(correctAnswer, sizeof(correctAnswer), answersFile) == NULL)
        {
            printf("Error reading answer.\n");
            fclose(questionsFile);
            fclose(answersFile);
            return;
        }

        // Check if the user's answer matches the correct answer
        trimWhitespace(correctAnswer); // Remove leading/trailing whitespace from correct answer
        trimWhitespace(userAnswer);    // Remove leading/trailing whitespace from user's answer
        toLowerCase(correctAnswer);    // Convert correct answer to lowercase
        toLowerCase(userAnswer);       // Convert user's answer to lowercase

        if (strcmp(correctAnswer, userAnswer) == 0)
        {
            printf("Correct answer!\n");
            correctCount++;
        }
        else
        {
            printf("Wrong answer. The correct answer is: %s\n", correctAnswer);
        }

        printf("\n");
    }

    fclose(questionsFile);
    fclose(answersFile);

    // Calculate and display the final score
    float finalScore = scoreCalculator(correctCount, numQuestions);
    system("clear");
    printf("You answered %d out of %d questions correctly.\n", correctCount, numQuestions);
    printf("Your final score is: %.2f%%\n", finalScore);

    // Update the leaderboard with the current session results
    updateLeaderboard(username, 1, numQuestions, finalScore);
    updateRankings();
}


void displayLeaderboard()
{
    FILE *file = fopen(LEADERBOARD_FILE, "r");
    if (file == NULL)
    {
        printf("Error opening leaderboard file.\n");
        return;
    }

    
    int rank = 1; // Initialize rank to 1

    printf("\nLeaderboard:\n");
    printf("Rank | Username          | Session | Questions Answered | Score   |\n");
    printf("---------------------------------------------------------------\n");

    // Read entries from the leaderboard file and calculate ranks
    while (fscanf(file, "%s %d %d %f", entry.username, &entry.sessionNumber, &entry.totalQuestionsAnswered, &entry.score) != EOF)
    {
        printf("%-4d | %-16s | %-7d | %-18d | %.2f%%\n", rank, entry.username, entry.sessionNumber, entry.totalQuestionsAnswered, entry.score);
        rank++; // Increment rank for the next entry
    }

    fclose(file);
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

int howManyLines(const char filename[])
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error opening file: %s\n", filename);
        return -1;
    }

    int count = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file))
    {
        count++;
    }

    fclose(file);
    return count;
}

int loadFileContent(const char filename[], char content[][64], int maxLines)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return -1;
    }

    int count = 0;
    while (count < maxLines && fgets(content[count], 64, file) != NULL)
    {
        content[count][strcspn(content[count], "\n")] = '\0'; // Remove newline character
        count++;
    }

    fclose(file);
    return count;
}

int fileloader(const char usersFile[], const char passwordsFile[], const char scoresFile[], user **ptr, int *maxUsers)
{
    int usersCount = howManyLines(usersFile);
    int passwordsCount = howManyLines(passwordsFile);
    int scoresCount = howManyLines(scoresFile);

    if (usersCount < 0 || passwordsCount < 0 || scoresCount < 0)
    {
        return -1;
    }

    int lineCount = usersCount < passwordsCount ? usersCount : passwordsCount;
    lineCount = lineCount < scoresCount ? lineCount : scoresCount;

    *ptr = malloc(lineCount * sizeof(user));
    if (*ptr == NULL)
    {
        printf("Memory allocation error\n");
        return -1;
    }

    char usersContent[lineCount][64];
    char passwordsContent[lineCount][64];
    char scoresContent[lineCount][64];

    if (loadFileContent(usersFile, usersContent, lineCount) != lineCount ||
        loadFileContent(passwordsFile, passwordsContent, lineCount) != lineCount ||
        loadFileContent(scoresFile, scoresContent, lineCount) != lineCount)
    {
        printf("Mismatch in number of lines between files\n");
        free(*ptr);
        return -1;
    }

    for (int i = 0; i < lineCount; i++)
    {
        strncpy((*ptr)[i].username, usersContent[i], sizeof((*ptr)[i].username) - 1);
        (*ptr)[i].username[sizeof((*ptr)[i].username) - 1] = '\0'; // Ensure null-terminated

        strncpy((*ptr)[i].password, passwordsContent[i], sizeof((*ptr)[i].password) - 1);
        (*ptr)[i].password[sizeof((*ptr)[i].password) - 1] = '\0'; // Ensure null-terminated

        sscanf(scoresContent[i], "Username: %s, Questions Answered: %d, Correct Answers: %d, Final Score: %f%%",
               (*ptr)[i].userScore.username, &(*ptr)[i].userScore.numQuestions, &(*ptr)[i].userScore.correctAnswers, &(*ptr)[i].userScore.finalScore);

        (*ptr)[i].id = i + 1; // Assign unique ID
    }

    *maxUsers = lineCount;
    return 0;
}

int saveUserToFile(const char *filename, const char *data)
{
  
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return -1;
    }
    fprintf(file, "%s\n", data);
    fclose(file);
    return 0;
}

int authenticateUser(user *users, int maxUsers, const char *username, const char *password)
{
    for (int i = 0; i < maxUsers; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            if (strcmp(users[i].password, password) == 0)
            {
                return i; // Return user index if authenticated
            }
            else
            {
                return -2; // Password incorrect
            }
        }
    }
    return -1; // Username not found
}

void signUp(user **users, int *maxUsers, const char *username, const char *password)
{
    *users = realloc(*users, (*maxUsers + 1) * sizeof(user));
    if (*users == NULL)
    {
        printf("Memory allocation error\n");
        return;
    }

    strncpy((*users)[*maxUsers].username, username, sizeof((*users)[*maxUsers].username) - 1);
    (*users)[*maxUsers].username[sizeof((*users)[*maxUsers].username) - 1] = '\0'; // Ensure null-terminated

    strncpy((*users)[*maxUsers].password, password, sizeof((*users)[*maxUsers].password) - 1);
    (*users)[*maxUsers].password[sizeof((*users)[*maxUsers].password) - 1] = '\0'; // Ensure null-terminated

    (*users)[*maxUsers].id = *maxUsers + 1; // Assign unique ID

    // Save to files
    saveUserToFile("users.txt", username);
    saveUserToFile("passwords.txt", password);

    (*maxUsers)++;
    printf("User signed up successfully.\n");
}

int login(user *users, int maxUsers,char username[],char password[])
{
    
    int tries = 3;

    printf("Please enter username: ");
    scanf("%31s", username);

    while (tries > 0)
    {
        printf("Please enter %s password: ", username);
        scanf("%31s", password);

        // Check if the user is admin
        if (strcmp(username, "admin") == 0 && strcmp(password, "Admin@11") == 0)
        {
            printf("Admin login successful. Welcome, admin!\n");
            return 9;
        }

        int userIndex = authenticateUser(users, maxUsers, username, password);
        if (userIndex >= 0)
        {
            printf("Login successful. Welcome, %s!\n", users[userIndex].username);
            return userIndex;
        }
        else if (userIndex == -2)
        {
            tries--;
            printf("Invalid password. Tries left: %d\n", tries);
        }
        else
        {
            printf("Username not found.\n");
            return -1;
        }
    }

    if (tries == 0)
    {
        printf("Too many failed attempts. Access denied.\n");
    }

    return -1;
}

void deleteLine(const char *filename, int lineNumber)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        fclose(file);
        printf("Error creating temporary file.\n");
        return;
    }

    char buffer[256];
    int currentLine = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        currentLine++;
        if (currentLine != lineNumber)
        {
            fputs(buffer, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Remove the original file and rename the temporary file
    remove(filename);
    rename("temp.txt", filename);
}

int editAnswer(const char *filename, int lineNumber, const char *newAnswer)
{
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("temp_answers.txt", "w");

    if (file == NULL || tempFile == NULL)
    {
        printf("Error opening files.\n");
        return -1;
    }

    char buffer[256];
    int currentLine = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        currentLine++;
        if (currentLine != lineNumber)
        {
            fprintf(tempFile, "%s", buffer);
        }
        else
        {
            fprintf(tempFile, "%s\n", newAnswer);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(filename);
    rename("temp_answers.txt", filename);

    printf("Answer edited successfully.\n");

    return 0;
}

int editByLineNumber(const char *filename, int lineNumber)
{
    FILE *file = fopen(filename, "r+");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return -1;
    }

    char buffer[256];
    int currentLine = 0;

    // Move to the desired line in the file
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        currentLine++;
        if (currentLine == lineNumber)
        {
            printf("Current content:\n%s\n", buffer);
            printf("Enter 'e' to edit this or 'd' to delete it: ");
            char choice;
            scanf(" %c", &choice); // Notice the space before %c to consume any leading whitespace

            if (choice == 'e' || choice == 'E')
            {
                printf("Enter the new content: ");
                scanf(" %[^\n]", buffer);               // Read the entire line including spaces
                fseek(file, -strlen(buffer), SEEK_CUR); // Move back to the beginning of the line
                fprintf(file, "%s", buffer);            // Write the new content to the file
                fclose(file);
                printf("Edited successfully.\n");

                // Prompt to edit the associated answer
                printf("Do you want to edit the associated answer? (y/n): ");
                char editChoice;
                scanf(" %c", &editChoice);
                if (editChoice == 'y' || editChoice == 'Y')
                {
                    char newAnswer[256];
                    printf("Enter the new answer: ");
                    scanf(" %[^\n]", newAnswer);
                    editAnswer("answers_questions.txt", lineNumber, newAnswer);
                }

                return 1; // Success
            }
            else if (choice == 'd' || choice == 'D')
            {
                fclose(file);
                deleteLine(filename, lineNumber); // Delete the line
                printf("Deleted successfully.\n");

                // Delete the corresponding answer from answers.txt
                deleteLine("answers_questions.txt", lineNumber);

                return 1; // Success
            }
            else
            {
                fclose(file);
                printf("Invalid choice.\n");
                return -1; // Failure
            }
        }
    }

    fclose(file);
    printf("Line number out of range.\n");
    return -1; // Failure
}

int editQuestion()
{
    char choice[2];
    int validChoice = 0;

    printf("Enter 'n' to choose by line number or 's' to choose by substring: ");
    scanf(" %1[^\n]", choice); // Read only one character

    if (choice[0] == 'n' || choice[0] == 'N')
    {
        int lineNumber;
        printf("Enter the line number: ");
        scanf("%d", &lineNumber);
        getchar(); // Consume newline character
        if (lineNumber <= 0)
        {
            printf("Invalid line number.\n");
            return -1;
        }
        return editByLineNumber("questions.txt", lineNumber);
    }
    else if (choice[0] == 's' || choice[0] == 'S')
    {
        char searchStr[256];
        printf("Enter a substring: ");
        scanf(" %[^\n]", searchStr); // Read the entire line including spaces

        int lineNumber = checker(searchStr, "questions.txt");
        if (lineNumber <= 0)
        {
            printf("No matching line found.\n");
            return -1;
        }
        return editByLineNumber("questions.txt", lineNumber);
    }
    else
    {
        printf("Invalid choice.\n");
        return -1;
    }
}

int deleteUser(const char *username)
{
    int userLineNumber = checker("users.txt", username);
    if (userLineNumber == -1)
    {
        printf("User not found.\n");
        return -1;
    }

    deleteLine("users.txt", userLineNumber);
    deleteLine("passwords.txt", userLineNumber);

    FILE *leaderboardFile = fopen("leaderboard.txt", "r");
    FILE *tempLeaderboardFile = fopen("temp_leaderboard.txt", "w");

    if (leaderboardFile == NULL || tempLeaderboardFile == NULL)
    {
        printf("Error opening leaderboard files.\n");
        return -1;
    }

    char buffer[256];

    // Remove all occurrences of the user's line from the leaderboard file
    while (fgets(buffer, sizeof(buffer), leaderboardFile) != NULL)
    {
        if (strstr(buffer, username) == NULL)
        {
            fprintf(tempLeaderboardFile, "%s", buffer);
        }
    }

    fclose(leaderboardFile);
    fclose(tempLeaderboardFile);

    remove("leaderboard.txt");
    rename("temp_leaderboard.txt", "leaderboard.txt");

    printf("User deleted successfully.\n");
    return 0;
}

int editAnswerQuestion()
{
    char choice[2];
    int validChoice = 0;

    printf("Enter 'n' to choose by line number or 's' to choose by substring: ");
    scanf(" %1[^\n]", choice); // Read only one character

    if (choice[0] == 'n' || choice[0] == 'N')
    {
        int lineNumber;
        printf("Enter the line number: ");
        scanf("%d", &lineNumber);
        getchar(); // Consume newline character
        if (lineNumber <= 0)
        {
            printf("Invalid line number.\n");
            return -1;
        }

        // Delete the related question from questions.txt
        deleteLine("questions.txt", lineNumber);

        // Delete the answer from answers.txt
        return editByLineNumber("answers.txt", lineNumber);
    }
    else if (choice[0] == 's' || choice[0] == 'S')
    {
        char searchStr[256];
        printf("Enter a substring: ");
        scanf(" %[^\n]", searchStr); // Read the entire line including spaces

        int lineNumber = checker(searchStr, "answers.txt");
        if (lineNumber <= 0)
        {
            printf("No matching line found.\n");
            return -1;
        }

        // Delete the related question from questions.txt
        deleteLine("questions.txt", lineNumber);

        // Edit the answer in answers.txt
        return editByLineNumber("answers.txt", lineNumber);
    }
    else
    {
        printf("Invalid choice.\n");
        return -1;
    }
}

void adminMenu()
{
    char choice;

    do
    {
        printf("\nAdmin Menu:\n");
        printf("1. Add user\n");
        printf("2. Delete user\n");
        printf("3. Add question\n");
        printf("4. Delete question\n");
        printf("5. Add answer\n");
        printf("6. Delete answer\n");
        printf("Q. Quit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice)
        {
        case '1':
            signUp(&p, MAXUSERS, username, password);
            break;
        case '2':
            printf("please enter the username of the user");
            scanf("%s", username);
            deleteUser(username);
            break;
        case '3':
            char tempquestion[500];
            saveUserToFile("questions.txt", tempquestion);
            break;
        case '4':
            editQuestion();
            break;
        case '5':
            char tempanswer[500];
            saveUserToFile("answers.txt", tempanswer);
            break;
        case '6':
            editAnswerQuestion();
            break;
        case 'q':
            break;
        case 'Q':
        break;
            printf("Exiting admin menu.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 'q' && choice != 'Q');
}

int main()
{
    user *users = NULL;
    char username[50], password[50];
    int maxUsers = 0;

    if (fileloader("users.txt", "passwords.txt", "scores.txt",&p, &maxUsers) == 0)
    {
        char choice;
        printf("Press Enter to sign up or 'l' to log in: ");
        choice = getchar();

        if (choice == 'l')
        {
            if (login(p, maxUsers,username,password)==9)
            {
                adminMenu();
            }
            else if (login(p, maxUsers,username,password) !=-1)
            {
                printf("welcom user");
            }
        }
        else
        {
            char username[32];
            char password[32];
            printf("Please enter username: ");
            scanf("%31s", username);
            printf("Please enter password: ");
            scanf("%31s", password);
            signUp(&users, &maxUsers, username, password);
        }
    }

    free(users);
    return 0;
}