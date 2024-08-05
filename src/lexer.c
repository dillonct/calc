#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include <stdio.h>

typedef struct {
    const char* input;
    int index;
} Lexer;

Lexer lexer;

static Token symbol_token(TokenType type) {
    Token new_token;
    new_token.type = type;
    new_token.number = 0;

    return new_token;
}

static Token number_token(TokenType type, double number) {
    Token new_token;
    new_token.type = type;
    new_token.number = number;

    return new_token;
}

static char peek_char() {
    return lexer.input[lexer.index];
}

static char peek_next_char() {
    return lexer.input[lexer.index + 1];
}

static char next_char() {
    char c = peek_char();
    lexer.index += 1;

    return c;
}

void init_lexer(const char* input) {
    lexer.input = input;
    lexer.index = 0;
}

Token next_token() {
    switch(peek_char()) {
        case '+':
            next_char();
            return symbol_token(TOKEN_ADD);
        case '-': 
            next_char();
            return symbol_token(TOKEN_SUB);
        case '*': 
            next_char();
            return symbol_token(TOKEN_MUL);
        case '/': 
            next_char();
            return symbol_token(TOKEN_DIV);
        case '%': 
            next_char();
            return symbol_token(TOKEN_REMAINDER);
        case '(': 
            next_char();
            return symbol_token(TOKEN_OPEN_PAREN);
        case ')': 
            next_char();
            return symbol_token(TOKEN_CLOSE_PAREN);
        case '\0':
            return symbol_token(TOKEN_ADD);
        default:
            if (isdigit(peek_char()) || peek_char() == '.') {
                int start_index = lexer.index;

                while (isdigit(peek_char())) next_char();
                if (peek_char() == '.' && isdigit(peek_next_char())) {
                    next_char(); // consume the . 

                    while (isdigit(peek_char())) {
                        next_char();
                    }
                }

                int end_index = lexer.index;

                int length = end_index - start_index + 1; 

                char str_slice[length + 1]; // include the null terminator
                strncpy(str_slice, lexer.input + start_index, length);
                str_slice[length] = '\0';

                float num = atof(str_slice);

                return number_token(TOKEN_NUMBER, num);
            } 

            return symbol_token(TOKEN_ERROR);
        }
}

Token peek_token() {
    int previous_index = lexer.index;
    Token token = next_token();
    lexer.index = previous_index; 

    return token;
}
