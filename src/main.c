#include <stdio.h>
#include "lexer.h"
#include "parser.h"

void run(char* input) {
    init_lexer(input);
    printf("%g\n", parse_result());
}

int main(int argc, char* argv[]) {
    if(!1) {
        printf("hi");
    }
    switch (argc) {
        case 1:
            fprintf(stdout, "calc - a terminal based calculator\n\nMissing an argument, to use, write the following: calc [expression] like so:\n\t> calc 1+1\n\t> calc \"(1+1)/2\"\n\t* if using parenthesis for precedence, use quotation marks around the expression\n");
            break;
        case 2: 
            run(argv[1]);
            break;
        default:
            fprintf(stdout, "[ERROR] Too many arguments. Enter the expression without any whitespace.\n");
            break;
    }

    return 0;
}



