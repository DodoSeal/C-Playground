#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../types/Token.h"

typedef struct Tokenizer Tokenizer;

struct Tokenizer {
    char *input;
    size_t input_len;
    size_t position;
    Token *tokens;
    size_t token_count;
    int line;
    int column;

    char (*peek)(Tokenizer *this, int offset);
    char (*advance)(Tokenizer *this);
    int (*is_eof)(Tokenizer *this);
    void (*skip_whitespace)(Tokenizer *this);
    Token* (*read_next)(Tokenizer *this);
    Token* (*tokenize_comment)(Tokenizer *this);
    Token* (*tokenize_digit)(Tokenizer *this);

    Token* (*run)(Tokenizer *this);
};

char peek(Tokenizer *this, int offset) {
    int pos = this->position + offset;

    if (this->is_eof(this)) return '\0';
    if (pos < 0 || pos > this->input_len) return '\0';

    return this->input[pos];
};

char advance(Tokenizer *this) {
    if (this->is_eof(this) || this->position + 1 > this->input_len) return '\0';

    return this->input[this->position++];
};

int is_eof(Tokenizer *this) {
    return (this->position > this->input_len);
};

void skip_whitespace(Tokenizer *this) {
    char next = this->peek(this, 0);
    while (this->position < this->input_len && isspace(next)) {
        this->advance(this);
    };
};

// TODO
Token *tokenize_comment(Tokenizer *this) {

};

Token *tokenize_digit(Tokenizer *this) {
    char value[64] = "";

    while (isdigit(this->peek(this, 0))) {
        strcat(value, this->advance(this));
    };

    if (this->peek(this, 0) == '.' && isdigit(this->peek(this, 1))) {
        this->advance(this);

        while (isdigit(this->peek(this, 0))) {
            strcat(value, this->advance(this));
        };
    };

    Token digit_token = {
        TOKEN_NUMBER,
        value,
        this->line,
        this->column
    };

    return &digit_token;
};

Token *read_next(Tokenizer *this) {
    this->skip_whitespace(this);
    if (this->is_eof(this)) {
        Token eof_token = {
            TOKEN_EOF,
            "",
            this->line,
            this->column
        };

        return &eof_token;
    };

    char current = this->peek(this, 0);
    char next = this->peek(this, 1);

    // TODO: Handle comments?
    // this->tokenize_comment(this);

    if (isdigit(current)) return this->tokenize_digit(this);
};

Token *run(Tokenizer *this) {
    Token *tokens[64] = {};

    while (!this->is_eof(this)) {
        Token *next = this->read_next(this);

        if (next->type == TOKEN_EOF) break;

        // TODO: somehow append next to tokens
    };

    return tokens;
};

Tokenizer *tokenizer_create(const char *input) {
    Tokenizer *this = malloc(sizeof(Tokenizer));
    if (!this) return NULL;

    this->input_len = strlen(input);
    this->input = malloc(this->input_len + 1);

    if (!this->input) {
        free(this);
        return NULL;
    };

    memcpy(this->input, input, this->input_len + 1);

    this->position = 0;
    this->token_count = 0;
    this->tokens = NULL;
    this->line = 0;
    this->column = 0;

    this->peek = peek;
    this->advance = advance;
    this->is_eof = is_eof;
    this->skip_whitespace = skip_whitespace;
    this->tokenize_comment = tokenize_comment;
    this->tokenize_digit = tokenize_digit;

    this->run = run;

    return this;
};