#ifndef _PARSER_H
#define _PARSER_H

#include "lexer.h"

typedef enum {
    FUNCTOR,
    BINARY,
    PRIMARY,
} ExprType;

typedef struct Expr Expr;

typedef struct {
    Token* identifier;
    size_t arity;
    size_t cap;
    Expr* args;
} Functor;

typedef struct {
    Token* identifier;
} Primary;

typedef struct {
    Expr* left;
    Token* op;
    Expr* right;
} Binary;

struct Expr{
    ExprType type;
    char* input;
    union {
        Functor functor;
        Primary primary;
        Binary  binary;
    } as;
};

Expr* parse(TokenList* list);
void print_expr(Expr* expr);
void destroy_expr(Expr* expr);


#endif //_PARSER_H