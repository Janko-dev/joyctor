#include "runtime.h"

void init_runtime(){

}

void interpret(char* input){
    TokenList list = {0};
    list.input = input;
    lex(&list);
    
    // print_tokens(&list);
    Expr* e = parse(&list);
    print_expr(e);
    printf("\n");

    destroy_expr(e);
    destroy_tokens(&list);
}