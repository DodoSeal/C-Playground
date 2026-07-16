#include <stdio.h>
#include <stdlib.h>
#include "tokenizer/tokenizer.h"

#include <ctype.h>

int main() {
    // Tokenize("const test = \"Hello, World!\";");

    Tokenizer *t = tokenizer_create("const value = \"Hello, World!\";");

    return 0;
};