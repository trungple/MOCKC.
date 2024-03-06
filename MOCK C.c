#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

typedef struct Player {
    char name[30];
    float luckyRatio;
    int guessedNumber;
} Player;

// Function to generate the random number form 0-9999
int setRandomNumber()
{
    srand(time(NULL));
    int result = (rand() % 9000) + 1000;
    return result;
}

// Check name
void checkInputName(char *name)
{
    int stringLength = strlen(name);
    while (stringLength>30)
    {
        printf("Invalid Player name. It is less than 30 characters.\nInput player's name again:");
        scanf("%s",name);
        stringLength = strlen(name);
    }
}

//Check number 
void checkInputNumber(int *a)
{
    while (*a>9999||*a<0)
    {
        printf("Invalid number. It must be 1-9999\n");
        scanf("%d",a);
    }
}

//Show table for user choose
void menu()
{
    printf("Press 'y' to continue.\nPress 'n' to finish and print out top 5 players\n");
}

//Check option of player
void checkOption(char *a)
{
    while(*a!='y'&&*a!='n')
    {
        printf("Invalid option. Enter your option again\n");
        menu();
        scanf(" %c",a);
    }
}

//Function to compare the rondam number with user's number and print the results in the required format
void printComparisonResult(int a, int b) {
    for (int i = 1000; i > 0; i /= 10) {
        int digitA = (a / i) % 10;
        int digitB = (b / i) % 10;

        if (digitA == digitB) {
            printf("%d", digitA);
        } else {
            printf("-");
        }
    }
}

//Function to load information of player into file
void savePlayerToFile(Player *player) {
    FILE *file = fopen("E:/cex/topLuckyPlayer.txt", "a+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s %d %.2f%%\n", player->name, player->guessedNumber, player->luckyRatio);
    fclose(file);
}

//Function to read information from file and printf out top 5 players
void findAndPrintTopPlayers() {
    FILE *file = fopen("E:/cex/topLuckyPlayer.txt", "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Player players[100];
    int numPlayers = 0;

    while (fscanf(file, "%s %d %f%%", players[numPlayers].name, &players[numPlayers].guessedNumber, &players[numPlayers].luckyRatio) == 3) {
        numPlayers++;
    }

    fclose(file);

    // Sort players based on lucky ratio in descending order
    for (int i = 0; i < numPlayers - 1; i++) {
        for (int j = i + 1; j < numPlayers; j++) {
            if (players[i].luckyRatio < players[j].luckyRatio) {
                Player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    // Print top 5 players
    printf("\nTop 5 Players (Highest Lucky Ratio):\n");
    printf("%-15s %-10s %-15s\n", "Player", "Number", "Lucky Ratio");
    printf("---------------------------------\n");
    for (int i = 0; i < 5 && i < numPlayers; i++) 
    {
        printf("%-15s %-10d %.2f%%\n", players[i].name, players[i].guessedNumber, players[i].luckyRatio);
    }
}

int main() {
    char userOption;    // variable stand for user's option
    Player newPlayer;   

    do {
        int randomNumber = setRandomNumber();
        int incorrectEntriesCount = 0;

        printf("Enter your name: ");
        scanf("%s", newPlayer.name);
        checkInputName(newPlayer.name);

        // allow people enter number until have a right number
        do {
            printf("Enter your number: ");
            scanf("%d", &newPlayer.guessedNumber);

            checkInputNumber(&newPlayer.guessedNumber);

            incorrectEntriesCount++;

            printComparisonResult(randomNumber, newPlayer.guessedNumber);
            printf("\n");

        } while (newPlayer.guessedNumber != randomNumber);

        newPlayer.luckyRatio = 100.00 / incorrectEntriesCount;

        savePlayerToFile(&newPlayer);

        printf("%s guessed the right number %d with a lucky ratio of %.2f%%", newPlayer.name, randomNumber, newPlayer.luckyRatio);

        printf("\nDo you want to continue?\n");

        menu();

        scanf(" %c", &userOption);
        
        checkOption(&userOption);

    } while (userOption == 'y');

    findAndPrintTopPlayers();
    return 0;
}