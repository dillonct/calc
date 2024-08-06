#include <ctype.h>
#include "lexer.h"

typedef struct {
    const char* input;
    int index;
} Lexer;

Lexer lexer;


static Token create_token(TokenType type, const char* start, int length) {
    Token new_token;
    new_token.type = type;
    new_token.start = start;
    new_token.length = length;

    return new_token;
}

static Token create_symbol_token(TokenType type) {
    return create_token(type, lexer.input + lexer.index, 1);
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
            return create_symbol_token(TOKEN_ADD);
        case '-': 
            next_char();
            return create_symbol_token(TOKEN_SUB);
        case '*': 
            next_char();
            return create_symbol_token(TOKEN_MUL);
        case '/': 
            next_char();
            return create_symbol_token(TOKEN_DIV);
        case '%': 
            next_char();
            return create_symbol_token(TOKEN_REMAINDER);
        case '(': 
            next_char();
            return create_symbol_token(TOKEN_OPEN_PAREN);
        case ')': 
            next_char();
            return create_symbol_token(TOKEN_CLOSE_PAREN);
        case '"': 
            next_char();
            break;
        case '\0':
            return create_symbol_token(TOKEN_EOL);
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

                int length = end_index - start_index; 

                return create_token(TOKEN_NUMBER, lexer.input + start_index, length);
            } 
            break;
        }

        // if it ever reaches here, there must be an unknown token
        // will be handled in parser
        next_char();
        return create_token(TOKEN_ERROR, lexer.input + lexer.index, 1);
}

Token peek_token() {
    int previous_index = lexer.index;
    Token token = next_token();
    lexer.index = previous_index; 

    return token;
}

const char* get_input() {
    return lexer.input;
}
