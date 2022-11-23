#include <stdio.h>
#include "lexer.h"
#include "parser.h"

int main(void){

    TokenList list = {0};
    char* input = "f(a, b, c) => g(b)";
    list.input = input;
    lex(&list);
    
    // print_tokens(&list);
    Expr* e = parse(&list);
    printf("Type: %d\n", e->type);

    destroy_tokens(&list);

    return 0;
}