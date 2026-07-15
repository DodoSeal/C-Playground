#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ROCK "rock"
#define PAPER "paper"
#define SCISSORS "scissors"

/**
 * Determines which choice is the winner
 * -1 = ERROR
 * 0 = TIE
 * 1 = PLAYER
 * 2 = BOT
 * @param player_choice The player's entered choice
 * @param bot_choice The random choice made by the program
 */
int determine_winner(char *player_choice, char *bot_choice) {
    if (strcmp(player_choice, bot_choice) == 0) return 0;

    if (strcmp(player_choice, ROCK) == 0) {
        if (strcmp(bot_choice, PAPER) == 0) return 2; else // Rock vs Paper (bot wins)
        if (strcmp(bot_choice, SCISSORS) == 0) return 1;   // Rock vs Scissors (player wins)
    } else if (strcmp(player_choice, PAPER) == 0) {
        if (strcmp(bot_choice, ROCK) == 0) return 1; else  // Paper vs Rock (player wins)
        if (strcmp(bot_choice, SCISSORS) == 0) return 2;   // Paper vs Scissors (bot wins)
    } else if (strcmp(player_choice, SCISSORS) == 0) {
        if (strcmp(bot_choice, ROCK) == 0) return 2; else  // Scissors vs Rock (bot wins)
        if (strcmp(bot_choice, PAPER) == 0) return 1;      // Scissors vs Paper (player wins)
    } else return -1;
};

/**
 * Returns a random integer between 1-3
 */
int make_bot_choice() {
    int random_number = rand() % (3 - 1 + 1) + 1;

    return random_number;
};

/**
 * Translates an integer between 1-3 into a valid game choice
 * 1 = ROCK
 * 2 = PAPER
 * 3 = SCISSORS
 * @param randomNum Integer between 1-3 that corresponds to Rock, Paper, Scissors
 * @param choice The place to store the translated bot_choice
 */
void translate_bot_choice(int randomNum, char *choice) {
    switch (randomNum) {
        case 1:
            snprintf(choice, sizeof(ROCK), ROCK);
            break;
        case 2:
            snprintf(choice, sizeof(PAPER), PAPER);
            break;
        case 3:
            snprintf(choice, sizeof(SCISSORS), SCISSORS);
            break;
    };
};

/**
 * Resets player_choice and bot_choice to "" then chooses a bot_choice
 * @param player_choice Reference to the player_choice char array
 * @param bot_choice Reference to the bot_choice char array
 */
void reset_choices(char *player_choice, char *bot_choice) {
    strcpy(player_choice, "");
    strcpy(bot_choice, "");
    translate_bot_choice(make_bot_choice(), bot_choice);
};

/**
 * Prints a header to the console with game instructions
 */
void print_game_info() {
    system("clear");
    printf("\nWelcome to Rock, Paper, Scissors!\n");
    printf("How to Play:\n");
    printf("- Allowed Choices: \"rock\", \"paper\", \"scissors\"\n");
    printf("- Do your best! :D\n\n");
};

/**
 * Prompts the player for their choice
 * @param player_choice Reference to the player_choice char array
 * @param player_choice_size sizeof(player_choice)
 * @param bot_choice Reference to the bot_choice char array
 */
void prompt_player_choice(char *player_choice, size_t player_choice_size, char *bot_choice) {
    printf("Enter your choice: ");

    if (fgets(player_choice, player_choice_size, stdin) != NULL) {
        player_choice[strcspn(player_choice, "\n \r")] = 0;
        bot_choice[strcspn(bot_choice, "\n \r")] = 0;

        printf("Bot Choice: %s\n", bot_choice);

        int winner = determine_winner(player_choice, bot_choice);

        switch(winner) {
            case -1:
                printf("\nYou entered an invalid choice!");
                break;
            case 0:
                system("clear");
                printf("\nYou Tied!");

                printf("\n\n");
                reset_choices(player_choice, bot_choice);
                prompt_player_choice(player_choice, player_choice_size, bot_choice);
                break;
            case 1:
                printf("\nYou Won!");
                break;
            case 2:
                printf("\nYou Lost!");
                break;
        };
    };
};

int main() {
    char player_choice[9];
    char bot_choice[9];

    srand(time(NULL));
    print_game_info();
    reset_choices(player_choice, bot_choice);
    prompt_player_choice(player_choice, sizeof(player_choice), bot_choice);

    return 0;
};