#ifndef _LEXER_H
#define _LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define Extend(n) (n == 0 ? 8 : (n*2))

typedef enum {
    NUMBER,             // number, float 
    IDENTIFIER,         // alphabetic identifier

    PLUS,               // +
    MINUS,              // -
    STAR,               // *
    SLASH,              // /
    WEDGE,              // ^

    OPEN_PAREN,         // (
    CLOSE_PAREN,        // )
} TokenType;

typedef struct {
    TokenType type;
    size_t start;
    size_t count;
} Token;

typedef struct {
    size_t count;
    size_t length;
    Token* tokens;
} TokenList;

void lex(TokenList* list, char* input);
void print_token(const char* input, Token* token);
void destroy_tokens(TokenList* list);

#endif //_LEXER_H