#ifndef _LEXER_H
#define _LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define Extend(n) (n == 0 ? 8 : (n*2))

// f(a, b, c)

typedef enum {
    NUMBER,             // number, float 
    IDENTIFIER,         // alphabetic identifier

    OPEN_PAREN,         // (
    CLOSE_PAREN,        // )
    COMMA,              // ,
    DERIVE,             // =>
} TokenType;

typedef struct {
    TokenType type;
    size_t start;
    size_t count;
} Token;

typedef struct {
    size_t count;
    size_t cap;
    char* input;
    Token* tokens;
} TokenList;

void lex(TokenList* list);
void print_token(char* input, Token* token);
void print_tokens(TokenList* list);
void destroy_tokens(TokenList* list);

#endif //_LEXER_H