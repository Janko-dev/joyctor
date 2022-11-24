#include <stdio.h>
#include "runtime.h"

int main(void){

    // init_runtime();

    char input[1024];
    printf("Welcome to REPL environment\n");
    while(1){
        printf("> ");
        if (!fgets(input, sizeof(input), stdin)){
            printf("\n");
            break;
        }
        // printf("<%s>\n", input);
        interpret(input);
    }

    return 0;
}