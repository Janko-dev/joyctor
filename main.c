#include <stdio.h>
#include "lexer.h"

int main(void){

    TokenList list = {0};
    char* input = ".67x + 2 * (5 + (23)^(2x))  - 800";
    lex(&list, input);

    for (size_t i = 0; i < list.count; i++) {
        print_token(input, list.tokens + i);
    }

    destroy_tokens(&list);

    return 0;
}