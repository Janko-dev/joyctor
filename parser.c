#include "parser.h"

Expr* new_binary(Expr* left, Token* op, Expr* right){
    Expr* result = (Expr*)malloc(sizeof(Expr));
    result->type = BINARY;
    result->binary = (Binary){left, op, right};
    return result;
}

Expr* new_functor(Token* id){
    Expr* result = (Expr*)calloc(1, sizeof(Expr));
    result->type = FUNCTOR;
    result->functor.identifier = id;
    return result;
}

void expect(TokenType type, TokenList* list, size_t* index){
    TokenType actual = list->tokens[*index].type;
    if (type != actual) {
        fprintf(stderr, "Expected type %d, but got type %d", type, actual);
    }
}

Expr* functor(TokenList* list, size_t* index){
    expect(IDENTIFIER, list, index);
    Token* id = list->tokens + *index;
    *index++;

    Expr* func = new_functor(id);
    expect(OPEN_PAREN, list, index);
    *index++;
    
    while (list->tokens[*index].type != CLOSE_PAREN) {
        Expr* arg = functor(list, index);
        if (list->tokens[*index].type != COMMA){
            expect(CLOSE_PAREN, list, index);
        }
    }
    *index++;
    return func;
}

Expr* derivation(TokenList* list, size_t* index){
    Expr* left = functor(list, index);
    while (list->tokens[*index].type == DERIVE){
        Token* op = list->tokens + *index;
        *index++;
        Expr* right = functor(list, index);
        left = new_binary(left, op, right);
    }
    return left;
}

Expr* parse(TokenList* list){
    size_t index = 0;
    Expr* result = derivation(list, &index);
    // Expr* result = &(Expr){.type=PRIMARY, .primary={&list->tokens[0]}};
    return result;
}

void destroy_expr(Expr* expr){

}