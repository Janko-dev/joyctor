#include "lexer.h"

void push_token(TokenList* list, Token token){
    if (list->count >= list->cap) {
        list->cap = Extend(list->cap);
        list->tokens = realloc(list->tokens, sizeof(Token) * list->cap);
    }

    list->tokens[list->count++] = token;
}

size_t push_digit(TokenList* list, char* c, size_t start){
    size_t count = 0;
    while (isdigit(c[count])) count++;

    if (c[count] == '.') {
        count++;
        while (isdigit(c[count])) count++;
    }
    
    push_token(list, (Token){NUMBER, start, count});
    return count;
} 

size_t push_identifier(TokenList* list, char* c, size_t start){
    size_t count = 0;
    while (isalpha(c[count])) count++;

    push_token(list, (Token){IDENTIFIER, start, count});
    return count;
}

void lex(TokenList* list){
    size_t input_length = strlen(list->input);
    size_t index = 0;
    while (index < input_length) {
        char* c = list->input + index;
        switch (*c) {
            case ',': push_token(list, (Token){COMMA, index, 1}); index++; break;
            case '=': {
                if (c[1] == '>') {
                    push_token(list, (Token){COMMA, index, 2}); 
                    index+=2;
                }
            } break;
            case '(': push_token(list, (Token){OPEN_PAREN,  index, 1}); index++; break;
            case ')': push_token(list, (Token){CLOSE_PAREN, index, 1}); index++; break;
            
            case ' ': case '\t': case '\r': index++; break;

            default: {
                if (isdigit(*c) || *c == '.') {
                    index += push_digit(list, c, index);
                } else if (isalpha(*c)){
                    index += push_identifier(list, c, index);
                }
            } break;
        }
    }
}

void print_tokens(TokenList* list){
    
    for (size_t i = 0; i < list->count; i++) {
        Token token = list->tokens[i];
        switch (token.type){
            case NUMBER:      printf("Number:      '"); break;
            case IDENTIFIER:  printf("Identifier:  '"); break;
            case COMMA:       printf("Comma:       '"); break;
            case OPEN_PAREN:  printf("Open paren:  '"); break;
            case CLOSE_PAREN: printf("Close paren: '"); break;
            case DERIVE:      printf("Derivation:  '"); break;
            default: break;
        }
        for (size_t i = token.start; i < token.start+token.count; i++){
            printf("%c", list->input[i]);
        }
        printf("'\n"); 
    }
    
}

void destroy_tokens(TokenList* list){
    free(list->tokens);
}