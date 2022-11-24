#include "parser.h"

Expr* new_binary(char* input, Expr* left, Token* op, Expr* right){
    Expr* result = (Expr*)malloc(sizeof(Expr));
    result->type = BINARY;
    result->input = input;
    result->as.binary = (Binary){left, op, right};
    return result;
}

Expr* new_functor(char* input, Token* id){
    Expr* result = (Expr*)calloc(1, sizeof(Expr));
    result->type = FUNCTOR;
    result->input = input;
    result->as.functor.identifier = id;
    return result;
}

Expr* new_primary(char* input, Token* id){
    Expr* result = (Expr*)calloc(1, sizeof(Expr));
    result->type = PRIMARY;
    result->input = input;
    result->as.primary.identifier = id;
    return result;
}

void push_functor_arg(Expr* func, Expr* arg){
    if (func->as.functor.arity >= func->as.functor.cap) {
        func->as.functor.cap = Extend(func->as.functor.cap);
        func->as.functor.args = realloc(func->as.functor.args, sizeof(Expr) * func->as.functor.cap);
    }

    func->as.functor.args[func->as.functor.arity++] = *arg;
}

void expect(TokenType type, TokenList* list, size_t* index){
    TokenType actual = list->tokens[*index].type;
    if (type != actual) {
        fprintf(stderr, "Expected type %d, but got type %d\n", type, actual);
    }
}

Expr* parse_functor(TokenList* list, size_t* index){
    expect(IDENTIFIER, list, index);
    Token* id = list->tokens + *index;
    (*index)++;

    Expr* expr;

    if (list->tokens[*index].type == OPEN_PAREN){
        expr = new_functor(list->input, id);
        (*index)++;

        while (list->tokens[*index].type != CLOSE_PAREN) {
            Expr* arg = parse_functor(list, index);
            push_functor_arg(expr, arg);
            if (list->tokens[*index].type == COMMA){
                (*index)++;
            } else {
                expect(CLOSE_PAREN, list, index);
            }
        }
        (*index)++;
    } else {
        expr = new_primary(list->input, id);
    }
    
    return expr;
}

Expr* parse_derivation(TokenList* list, size_t* index){
    Expr* left = parse_functor(list, index);
    while (list->tokens[*index].type == DERIVE){
        Token* op = list->tokens + *index;
        (*index)++;
        Expr* right = parse_functor(list, index);
        left = new_binary(list->input, left, op, right);
    }
    return left;
}

Expr* parse(TokenList* list){
    size_t index = 0;
    Expr* result = parse_derivation(list, &index);
    return result;
}

void destroy_expr(Expr* expr){

    switch (expr->type){
        case BINARY: {
            destroy_expr(expr->as.binary.left);
            destroy_expr(expr->as.binary.right);
            free(expr);
        } break;
        case PRIMARY: {
            free(expr);
        } break;
        case FUNCTOR: {
            for (size_t i = 0; i < expr->as.functor.arity; i++){
                destroy_expr(expr->as.functor.args + i);
            }
            free(expr);
        }
    }
}

void print_expr(Expr* expr){
    switch (expr->type){
        case BINARY: {
            print_expr(expr->as.binary.left);
            printf(" ");
            print_token(expr->input, expr->as.binary.op);
            printf(" ");
            print_expr(expr->as.binary.right);
        } break;
        case PRIMARY: {
            print_token(expr->input, expr->as.primary.identifier);
        } break;
        case FUNCTOR: {
            print_token(expr->input, expr->as.functor.identifier);
            printf("(");
            for (size_t i = 0; i < expr->as.functor.arity; i++){
                print_expr(expr->as.functor.args + i);
                if (i != expr->as.functor.arity - 1) {
                    printf(", ");
                }
            }
            printf(")");
        }
    }
}