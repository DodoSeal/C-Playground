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

    char (*peek)(Tokenizer *this, int offset);
    char (*advance)(Tokenizer *this);
    int (*is_eof)(Tokenizer *this);

    Token (*run)(Tokenizer *this);
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

Token *run(Tokenizer *this) {
    // TODO: Do tokenizer thing duhhhhh
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

    this->peek = peek;
    this->advance = advance;
    this->is_eof = is_eof;

    this->run = run;

    return this;
};