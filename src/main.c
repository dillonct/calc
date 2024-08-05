#include <stdio.h>
#include "lexer.h"
#include "parser.h"
int run(char* input);

int main(int argc, char* argv[]) {
    switch (argc) {
        case 1:
            fprintf(stdout, "calc - a terminal based calculator\n\nMissing an argument, to use, write the following: calc [expression]\n");
            break;
        case 2: 
            run(argv[1]);
            break;
        default:
            fprintf(stdout, "[ERROR] Too many arguments. Enter the expression without any whitespace.\n");
            break;
    }
}

void print_formatted_number(float num) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%.15g", num);

    printf("%s\n", buffer);
}

int run(char* input) {
    init_lexer(input);
    printf("%g\n", parse_expression());

    return 0; // placeholder
}


