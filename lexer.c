#include "lexer.h"

void push_token(TokenList* list, Token token){
    if (list->count >= list->length) {
        list->length = Extend(list->length);
        list->tokens = realloc(list->tokens, sizeof(Token) * list->length);
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

void lex(TokenList* list, char* input){
    size_t input_length = strlen(input);
    size_t index = 0;
    while (index < input_length) {
        char* c = input + index;
        switch (*c) {
            case '+': push_token(list, (Token){PLUS,  index, 1}); index++; break;
            case '-': push_token(list, (Token){MINUS, index, 1}); index++; break;
            case '*': push_token(list, (Token){STAR,  index, 1}); index++; break;
            case '/': push_token(list, (Token){SLASH, index, 1}); index++; break;
            case '^': push_token(list, (Token){WEDGE, index, 1}); index++; break;

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

void print_token(const char* input, Token* token){
    switch (token->type){
        case NUMBER:     printf("Number: <"); break;
        case IDENTIFIER: printf("Identifier: <"); break;
        default:         printf("Symbol: <"); break;
    }
    for (size_t i = token->start; i < token->start+token->count; i++){
        printf("%c", input[i]);
    }
    printf(">\n"); 
}

void destroy_tokens(TokenList* list){
    free(list->tokens);
}