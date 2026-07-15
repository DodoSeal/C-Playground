#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "../types/Token.h"

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
Token read_next() {
    skip_whitespace();

    // TODO: Make EOF Token
    if (is_eof()) {
        Token eof_token = { TOKEN_EOF, "", line, column };
        return eof_token;
    };

    char current = peek(0);
    char next = peek(1);

    if (current == '/' && next == '/') {
        advance();
        advance();

        if (peek(0) == ' ') advance();

        size_t comment_cap = 64;
        size_t comment_len = 0;
        char *comment_value = malloc(comment_cap);
        
        while (!is_eof() && peek(0) != '\n' && peek(0) != '\0') {
            if (comment_len + 1 >= comment_cap) {
                comment_cap *= 2;

                char *temp = realloc(comment_value, comment_cap);
                comment_value = temp;
            };

            comment_value[comment_len++] = advance();
        };

        comment_value[comment_len] = '\0';

        Token comment_token = { TOKEN_COMMENT, comment_value, line, column };

        return comment_token;
    };
};

/**
 * @param data Source code
 */
Token *Tokenize(char *data) {
    input_len = strlen(data);
    input = malloc(input_len + 1);

    memcpy(input, data, input_len + 1);
    position = 0;

    size_t token_cap = 64, token_len = 0;
    Token *tokens = malloc(token_cap * sizeof(Token));

    while (!is_eof()) {
        Token next_token = read_next();

        if (token_len + 1 >= token_cap) {
            token_cap *= 2;
            tokens = realloc(tokens, token_cap * sizeof(Token));
        };
        tokens[token_len++] = next_token;
        if (next_token.type == TOKEN_EOF) break;

        printf("\nTOKEN:\nTYPE: %d\nVALUE: %s\n", next_token.type, next_token.value);
    };

    // Free memory allocated once we are done
    free(input);

    return tokens;
};