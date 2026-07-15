#ifndef TOKEN_H_
#define TOKEN_H_

typedef enum {
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_QUOTATION,
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_OPERATOR,
    TOKEN_SYMBOL,
    TOKEN_COMMENT,
    TOKEN_WHITESPACE,
    TOKEN_UNKNOWN,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    const char *value;
    int line;
    int column;
} Token;

#endif