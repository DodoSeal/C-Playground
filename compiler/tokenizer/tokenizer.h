#include "../types/Token.h"

#ifndef TOKENIZER_H_
#define TOKENIZER_H_

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

Tokenizer *tokenizer_create(const char *input);

#endif