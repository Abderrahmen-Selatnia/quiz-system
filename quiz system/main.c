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




user *p;
char username[50], password[50];

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
        if (checker(filename,valuetoD) == 0)
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
        if (checker(filename,valuetoD) == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
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


void greeting(const char *title)
{
    printf("\033[0;32m");
    printf("░░▒█░░▒█░░▒█▀▀▀░░▒█░░░░░▒█▀▀▄░░▒█▀▀▀█░░▒█▀▄▀█░░░░▀▀█▀▀░░▒█▀▀▀█▒░░\n");
    printf("░░▒█▒█▒█░░▒█▀▀▀░░▒█░░░░░▒█░░░░░▒█░░▒█░░▒█▒█▒█░░░░░▒█░░░░▒█░░▒█▒░░\n");
    printf("░░▒▀▄▀▄▀░░▒█▄▄▄░░▒█▄▄█░░▒█▄▄▀░░▒█▄▄▄█░░▒█░░▒█░░░░░▒█░░░░▒█▄▄▄█▒░░\n");
    printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
    printf("░▒█▀▀█░▒█░▒█░▀█▀░▒█▀▀▀█░░░▒█▀▀▀█░▒█░░▒█░▒█▀▀▀█░▀▀█▀▀░▒█▀▀▀░▒█▀▄▀█\n");
    printf("░▒█░▒█░▒█░▒█░▒█░░░▄▄▄▀▀░░░░▀▀▀▄▄░▒▀▄▄▄▀░░▀▀▀▄▄░░▒█░░░▒█▀▀▀░▒█▒█▒█\n");
    printf("░░▀▀█▄░░▀▄▄▀░▄█▄░▒█▄▄▄█░░░▒█▄▄▄█░░░▒█░░░▒█▄▄▄█░░▒█░░░▒█▄▄▄░▒█░░▒█\n");
    printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
    printf("░░░░░░░░░░░░░░░░░▒▓ Press |Enter| to log in ▓▒░░░░░░░░░░░░░░░░░░░\n");
    printf("░░░░░░░░░░░╔══════════════════════════════════════╗░░░░░░░░░░░░░░\n");
    printf("░░░░░░░░░░░║   Created by: SELATNIA ABDERRAHMEN   ║░░░░░░░░░░░░░░\n");
    printf("░░░░░░░░░░░╚══════════════════════════════════════╝░░░░░░░░░░░░░░\n");
    printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
    printf("*****************************************************************\n");
    printf("\033[0m");
}

int checker(const char *filename, char value[])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return -1;
    }

    char line[100];
    int lineNumber = 0;
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0'; // Remove newline character
        if (strcmp(line, value) == 0)
        {
            fclose(file);
            return lineNumber;
        }
        lineNumber++;
    }

    fclose(file);
    return -1; // Not found
}

bool hasSpace(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ')
        {
            return true; // Found a space character
        }
    }
    return false; // No space character found
}

int passwordvalidation(char p[])
{
    bool hasnumber = false;
    bool hasspecialcharacter = false;
    bool haslowercharcter = false;
    bool neededlength = false;
    bool hasasymbole = false;
   

    int length = strlen(p); // Calculate the length once

    if (length >= 8)
    {
        neededlength = true;
    }

    for (int i = 0; i < length; i++)
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

    if(hasSpace(p)){
        printf("no spases are allowed");
        
    }
    if (!neededlength)
    {
        printf("* Password must be at least 8 characters long *\n");
    }
    if (!hasasymbole)
    {
        printf("* Your password must have a symbol *\n");
    }
    if (!haslowercharcter)
    {
        printf("* Your password must have a lowercase character *\n");
    }
    if (!hasspecialcharacter)
    {
        printf("* Your password must have an uppercase letter *\n");
    }
    if (!hasnumber)
    {
        printf("* Your password must have a number *\n");
    }

    if (!hasSpace(p) && hasspecialcharacter && haslowercharcter && neededlength && hasasymbole)
    {
        return 1; // All criteria met
    }
    else
    {
        return 0; // Criteria not met
    }
}

int howManyLines(const char filename[])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s ",filename);
        return -1;
    }

    int lines = 0;
    char ch;
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
    system("clear");
    printf("this is the leader bord");
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

bool saveUserToFile(const char *filename, const char *data)
{
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return false;
    }
    fprintf(file, "%s\n", data);
    fclose(file);
    return true;
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

int usernamevalidation(user *p, int maxUsers,char username[])
{
    if (hasSpace(username)){
        printf("no spases allowed");
        return 0;
    }
    for (int i = 0; i < maxUsers; i++)
    { // Iterate up to maxUsers
        if (strcasecmp(p[i].username, username) == 0)
        {             // Check if username matches
            return 1; // Username already exists
        }
    }
    return 0; // Username is available
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

        char filename[20];
        printf("Enter 'q' to edit question or 'a' to edit answer: ");
        scanf(" %1[^\n]", choice); // Read only one character

        if (choice[0] == 'q' || choice[0] == 'Q')
        {
            return editByLineNumber("questions.txt", lineNumber);
        }
        else if (choice[0] == 'a' || choice[0] == 'A')
        {
            return editByLineNumber("answers.txt", lineNumber);
        }
        else
        {
            printf("Invalid choice.\n");
            return -1;
        }
    }
    else if (choice[0] == 's' || choice[0] == 'S')
    {
        char searchStr[256];
        printf("Enter a substring: ");
        scanf(" %[^\n]", searchStr); // Read the entire line including spaces

        // Implement checker function logic to find line number
        int lineNumber = 1; // Assume lineNumber is found by checker function

        char filename[20];
        printf("Enter 'q' to edit question or 'a' to edit answer: ");
        scanf(" %1[^\n]", choice); // Read only one character

        if (choice[0] == 'q' || choice[0] == 'Q')
        {
            return editByLineNumber("questions.txt", lineNumber);
        }
        else if (choice[0] == 'a' || choice[0] == 'A')
        {
            return editByLineNumber("answers.txt", lineNumber);
        }
        else
        {
            printf("Invalid choice.\n");
            return -1;
        }
    }
    else
    {
        printf("Invalid choice.\n");
        return -1;
    }
}

int editByLineNumber(const char *filename, int lineNumber)
{
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("temp_file.txt", "w");

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
            printf("Current content:\n%s", buffer);
            printf("Enter 'e' to edit this or 'd' to delete it: ");
            char choice;
            scanf(" %c", &choice);

            if (choice == 'e' || choice == 'E')
            {
                printf("Enter the new content: ");
                char newContent[256];
                getchar(); // Consume the newline left by previous scanf
                fgets(newContent, sizeof(newContent), stdin);
                newContent[strcspn(newContent, "\n")] = '\0'; // Remove the newline character
                fprintf(tempFile, "%s\n", newContent);
                printf("Edited successfully.\n");
            }
            else if (choice == 'd' || choice == 'D')
            {
                printf("Deleted successfully.\n");
                // Skip writing this line to the temporary file
            }
            else
            {
                fprintf(tempFile, "%s", buffer); // Write the original content if invalid choice
                printf("Invalid choice. No changes made.\n");
            }
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the updated content
    remove(filename);
    rename("temp_file.txt", filename);

    return 1; // Success
}

int login(user *users, int maxUsers,char username[],char password[])
{
    int adminindex = checker("users.txt", "admin");
    int tries = 3;

    printf("Please enter username: ");
    scanf("%31s", username);
    if (!usernamevalidation(users, maxUsers, username))
    {
       
    
    
        do
        {
            printf("Please enter a valid username: ");
            scanf("%31s", username);
            tries--;
            if (tries==0)
            {
                printf("sespesious actions ");
                exit(0);
            }

        } while (!usernamevalidation(users, maxUsers, username));
        
    }
    tries = 3;
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
        if(userIndex==adminindex){
            printf("Admin login successful. Welcome, admin!\n");
            return 9;
        }
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

int deleteUser(user *users)
{
    const int MAX_USERS = 100;
    
    int numUsers = howManyLines("users.txt");
    if (numUsers == -1)
    {
        return -1;
    }

    printf("Available users:\n");
    for (int i = 0; i <= numUsers; i++)
    {
        printf("%d. %s\n", i + 1, users[i].username);
    }

    char username[MAX_USERNAME_LENGTH];
    printf("Enter the username of the user to delete: ");
    scanf("%s", username);

    int userLineNumber = -1;
    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            userLineNumber = i + 1; // Assuming line numbers start from 1
            break;
        }
    }

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

void signUp(user *users, int maxUsers)
{
    char username[32];
    char password[32];
    int attempts = 0;

    do
    {
        printf("Enter username: ");
        scanf("%s", username);
        getchar(); // Consume newline character

        if (usernamevalidation(users, maxUsers, username))
        {
            printf("Username already exists. Please choose a different username.\n");
        }
        else
        {
            break; // Username is valid
        }
        attempts++;
    } while (attempts < 4);

    if (attempts >= 4)
    {
        printf("Maximum attempts reached. Exiting sign up process.\n");
        return;
    }

    attempts = 0;

    do
    {
        printf("Enter password: ");
        scanf("%s", password);
        getchar(); // Consume newline character

        if (passwordvalidation(password))
        {
            break; // Password is valid
        }
        attempts++;
    } while (attempts < 4);

    if (attempts >= 4)
    {
        printf("Maximum attempts reached. Exiting sign up process.\n");
        return;
    }

    if (saveUserToFile("users.txt", username) && saveUserToFile("passwords.txt", password))
    {
        printf("User signed up successfully.\n");
        maxUsers++;
    }
    else
    {
        printf("Error saving user information.\n");
    }
}

int fileloader(user **ptr, int *maxUsers)
{
    const char *usersFile = "users.txt";
    const char *passwordsFile = "passwords.txt";
    const char *scoresFile = "scores.txt";
    int MAX_PASSWORD_LENGTH = 32;
    int numberOfUsers = howManyLines(usersFile);
    if (numberOfUsers < 0)
    {
        printf("Error counting lines in %s\n", usersFile);
        return -1;
    }

    *maxUsers = numberOfUsers;
    *ptr = (user *)malloc(numberOfUsers * sizeof(user));
    if (*ptr == NULL)
    {
        printf("Memory allocation error\n");
        return -1;
    }

    FILE *usersPtr = fopen(usersFile, "r");
    FILE *passwordsPtr = fopen(passwordsFile, "r");
    FILE *scoresPtr = fopen(scoresFile, "r");
    if (usersPtr == NULL || passwordsPtr == NULL)
    {
        printf("Error opening files.\n");
        free(*ptr);
        return -1;
    }

    char userLine[MAX_USERNAME_LENGTH];
    char passLine[MAX_PASSWORD_LENGTH];
    char line[100];
    for (int i = 0; i < numberOfUsers; i++)
    {
        if (fgets(userLine, sizeof(userLine), usersPtr) == NULL)
        {
            printf("Error reading line %d from %s\n", i + 1, usersFile);
            
        }
        userLine[strcspn(userLine, "\n")] = '\0'; // Remove newline character
        strcpy((*ptr)[i].username, userLine);

        if (fgets(passLine, sizeof(passLine), passwordsPtr) == NULL)
        {
            printf("Error reading line %d from %s\n", i + 1, passwordsFile);
            
        }
        passLine[strcspn(passLine, "\n")] = '\0'; // Remove newline character
        strcpy((*ptr)[i].password, passLine);

        if (fgets(line, sizeof(line),scoresPtr) == NULL)
        {
            printf("Error reading line %d from %s\n", i + 1, scoresFile);
            
        }

        sscanf(line, "%d %d %f", &((*ptr + i)->userScore.numQuestions), &((*ptr + i)->userScore.correctAnswers), &((*ptr + i)->userScore.finalScore));
    }

    fclose(usersPtr);
    fclose(passwordsPtr);
    return 0;
}

void printinfile(const char *filename)
{
    char inputString[1000];
    printf("Enter a string (spaces, symbols, characters, and integers allowed):\n");
    scanf(" %[^\n]", inputString); // Note the space before %[^\n]

    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    fprintf(file, "%s\n", inputString);

    fclose(file);
}

int editQuestionOrAnswer(const char *filename, const char *associatedFilename, int lineNumber, const char *type)
{
    return editByLineNumber(filename, lineNumber);
}

void editAnswerorQuestion()
{
    while (1)
    {
        char choice[2];
        printf("Enter 'q' to edit question, 'a' to edit answer, or 'e' to exit: ");
        scanf(" %1[^\n]", choice); // Read only one character

        if (choice[0] == 'q' || choice[0] == 'Q')
        {
            printf("Enter the line number: ");
            int lineNumber;
            scanf("%d", &lineNumber);
            getchar(); // Consume newline character
            if (editQuestionOrAnswer("questions.txt", "answers.txt", lineNumber, "answer") == 1)
            {
                printf("Do you want to edit the associated answer? (y/n): ");
                char editChoice;
                scanf(" %c", &editChoice);
                if (editChoice == 'y' || editChoice == 'Y')
                {
                    editByLineNumber("answers.txt", lineNumber);
                }
            }
        }
        else if (choice[0] == 'a' || choice[0] == 'A')
        {
            printf("Enter the line number: ");
            int lineNumber;
            scanf("%d", &lineNumber);
            getchar(); // Consume newline character
            if (editQuestionOrAnswer("answers.txt", "questions.txt", lineNumber, "question") == 1)
            {
                printf("Do you want to edit the associated question? (y/n): ");
                char editChoice;
                scanf(" %c", &editChoice);
                if (editChoice == 'y' || editChoice == 'Y')
                {
                    editByLineNumber("questions.txt", lineNumber);
                }
            }
        }
        else if (choice[0] == 'e' || choice[0] == 'E')
        {
            printf("Exiting...\n");
            break;
        }
        else
        {
            printf("Invalid choice.\n");
        }
    }
}

void adminMenu()
{
    char choice;
    system("clear");
    do
    {
        
        printf("\nAdmin Menu:\n");
        printf("1. Add user\n");
        printf("2. Delete user\n");
        printf("3. Add question\n");
        printf("4. Add answer\n");
        printf("5. Edit/D question||answer\n");
        printf("6. Display the leaderboard\n");
        printf("Q. Quit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice)
        {
        case '1':
            system("clear");
            fileloader(&p, &MAXUSERS);
            signUp(p, MAXUSERS);
            
            break;
        case '2':
            system("clear");
            deleteUser(p);
            
            break;
        case '3':
            system("clear");
            printf("please enter the question you want to add:\n>");
            printinfile("questions.txt");
            break;
        case '4':
            system("clear");
            printf("please enter the answer :\n>");
            printinfile("answers.txt");
            break;
        case '5':
            system("clear");
            editAnswerorQuestion();
            break;
        case '6':
            system("clear");
            printf("this is the leader bord:");
            displayLeaderboard();

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

    fileloader(&p, &MAXUSERS);
  

    char choice;
    greeting("hello");
    choice = getchar();

    if (choice == '\n')
    {
        if (login(p,MAXUSERS, username, password) == 9)
        {
            adminMenu();
        }
        else if (login(p,MAXUSERS, username, password) != -1)
        {
            printf("welcom user");
            quizUser(username);
            displayLeaderboard();
        }
        }
        else
        {
            
        }

        free(p);
        return 0;
}