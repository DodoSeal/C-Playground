#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int position = 0;
int line = 0;
int column = 0;

char *input = NULL;
int input_len = 0;

int is_eof() {
    return (position >= input_len);
};

/**
 * Peeks at next character
 * @param offset
 * @returns Character at (position + offset)
 */
char peek(int offset) {
    int pos = position + offset;

    if (pos < 0 || pos >= input_len) return '\0';

    return input[pos];
};

/**
 * Advances position
 * @returns Character at new position
 */
char advance() {
    if (is_eof() || (position + 1) > input_len) return '\0';

    return input[position++];
};

int is_number(char *data) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^[0-9]+$", REG_EXTENDED);
    if (ret != 0) {
        printf("Could not compile regex pattern!");
        return 0;
    };

    ret = regexec(&regex, data, 0, NULL, 0);
    regfree(&regex);

    return !ret;
};

int is_letter(char *data) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^[a-zA-Z]+$", REG_EXTENDED);
    if (ret != 0) {
        printf("Could not compile regex pattern!");
        return 0;
    };

    ret = regexec(&regex, data, 0, NULL, 0);
    regfree(&regex);
    
    return !ret;
};

int is_operator(char *data) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^[+*/%=!<>&|^~-]+$", REG_EXTENDED);
    if (ret != 0) {
        printf("Could not compile regex pattern!");
        return 0;
    };

    ret = regexec(&regex, data, 0, NULL, 0);
    regfree(&regex);
    
    return !ret;
};

int is_punctuation(char *data) {
    regex_t regex;
    int ret;

    ret = regcomp(&regex, "^[;(){}[],.]+$", REG_EXTENDED);
    if (ret != 0) {
        printf("Could not compile regex pattern!");
        return 0;
    };

    ret = regexec(&regex, data, 0, NULL, 0);
    regfree(&regex);
    
    return !ret;
};

void skip_whitespace() {
    regex_t regex;
    int ret;
    char data = peek(0);

    ret = regcomp(&regex, "^[[:space:]]+$", REG_EXTENDED);
    if (ret != 0) {
        printf("Could not compile regex pattern!");
        return;
    };

    ret = regexec(&regex, &data, 0, NULL, 0);
    regfree(&regex);
    
    while (!ret) {
        advance();
    };
};

// TODO: Make this return a Token
void read_next() {
    skip_whitespace();

    // TODO: Make EOF Token
    // if (is_eof()) return;

    char current = peek(0);
    char next = peek(1);

    if (current == "/" && next == "/") {
        advance();
        advance();

        if (peek(0) == " ") advance();

        // TODO: Handle comment tokens
        // return;
    };

    
};

/**
 * @param data Source code
 */
void Tokenize(char *data) {
    input_len = strlen(data);
    input = malloc(input_len + 1);

    memcpy(input, data, input_len + 1);
    position = 0;

    printf("\nFull Input: %s", input);
    printf("\nPeek(0): %c", peek(0));
    printf("\nAdvance(): %c", advance());

    // Free memory allocated once we are done
    free(input);
};