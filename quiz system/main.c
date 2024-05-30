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
};
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

void displayLeaderboard(){
    FILE *file = fopen(LEADERBOARD_FILE, "r");
if (file == NULL)
{
    printf("Error opening leaderboard file.\n");
    return;
}

struct LeaderboardEntry entry;
int rank = 1; // Initialize rank to 1

printf("\nLeaderboard:\n");
printf("Rank | Username       | Session | Questions Answered | Score\n");
printf("---------------------------------------------------------\n");

// Read entries from the leaderboard file and calculate ranks
while (fscanf(file, "%s %d %d %f", entry.username, &entry.sessionNumber, &entry.totalQuestionsAnswered, &entry.score) != EOF)
{
    float percentage = (entry.score / (float)(entry.totalQuestionsAnswered * 100)) * 100.0f; // Calculate percentage
    printf("%-4d | %-15s | %-7d | %-18d | %.2f%%\n", rank, entry.username, entry.sessionNumber, entry.totalQuestionsAnswered, percentage);
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

void deleteuserS(user *p, int id)
{
    if ((p + id)->id != 0)
    {
        (p + id)->id = 0;
        strcpy((p + id)->username, "0");
        strcpy((p + id)->password, "0");
        (p + id)->userScore.finalScore = 0;
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
            sscanf(buffer, "Username: %s, Questions Answered: %d, Correct Answers: %d, Final Score: %f%%",
                   &(*ptr)[count].username, &(*ptr)[count].userScore.numQuestions, &(*ptr)[count].userScore.correctAnswers, &(*ptr)[count].userScore.finalScore);
            count++;
        
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
    int userId = -1; // Store the ID of the user if found

    while (triesLeft > 0)
    {
        printf("Please enter username: ");
        scanf("%s", username);

        // Search for the username in the user array
        for (int i = 0; i < MAXUSERS; i++)
        {
            if (strcmp(ptr[i].username, username) == 0)
            {
                userId = i; // Store the ID of the user
                break;
            }
        }

        if (strcmp(username, "admin") == 0)
        {
            printf("Username found. Please enter admin password: ");
            scanf("%s", password);

            // Compare the entered password with the admin's password
            if (strcmp("adminpassword", password) == 0)
            {
                printf("Admin login successful!\n");
                return 9; // Return 9 for admin login
            }
            else
            {
                triesLeft--;
                printf("Invalid admin password. Tries left: %d\n", triesLeft);
            }
        }
        else if (userId != -1)
        { // Regular user login
            printf("Username found. Please enter password: ");
            scanf("%s", password);

            // Compare the entered password with the user's password
            if (strcmp(ptr[userId].password, password) == 0)
            {
                printf("User login successful!\n");
                return 1; // Return 1 for regular user login
            }
            else
            {
                triesLeft--;
                printf("Invalid password. Tries left: %d\n", triesLeft);
            }
        }
        else
        {
            triesLeft--;
            printf("Username not found. Tries left: %d\n", triesLeft);
        }
    }

    printf("No more tries left. Exiting...\n");
    return -1; // Return -1 for failed login attempts
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
        printf("Loaded users with scores.\n");

        // Print loaded users with scores for demonstration
        for (int i = 0; i < MAXUSERS; i++)
        {
            printf("User %d - Username: %s, Questions Answered: %d, Correct Answers: %d, Final Score: %.2f%%\n",
                   users[i].id, users[i].username, users[i].userScore.numQuestions,
                   users[i].userScore.correctAnswers, users[i].userScore.finalScore);
        }

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

                quizUser(username);
                displayLeaderboard();
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
