#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
char* peek(int offset) {
    int pos = position + offset;

    if (pos < 0 || pos >= input_len) return "\0";

    return &input[pos];
};

/**
 * Advances position
 * @returns Character at new position
 */
char* advance() {
    if (is_eof() || (position + 1) > input_len) return "\0";

    return &input[position++];
};

/**
 * @param data Source code
 */
void Tokenize(char *data) {
    input_len = strlen(data);
    input = malloc(input_len + 1);

    memcpy(input, data, input_len + 1);
    position = 0;

    printf("%s", input);

    // Free memory allocated once we are done
    free(input);
};