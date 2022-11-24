#ifndef _RUNTIME_H
#define _RUNTIME_H

#include "lexer.h"
#include "parser.h"

void init_runtime();
void interpret(char* input);

#endif //_RUNTIME_H