#include <math.h>
#include <stdio.h>
#include "lexer.h"

float parse_expression();

static void match_token_type(TokenType type) {
    if (next_token().type == type) {
       printf("MATCH"); 
    }
       printf("NO MATCH"); 
}

static float parse_factor() {
    float value = 0;
    Token token = peek_token();

    switch(token.type) {
        case TOKEN_NUMBER:
            next_token();
            value = token.number;
            break;
        case TOKEN_OPEN_PAREN:
            next_token();
            value = parse_expression();
            match_token_type(TOKEN_CLOSE_PAREN);
            break;
        default: 
            break;
    }

    return value;
}
static float parse_term() {
    float value = parse_factor();
    while (1) {
        Token token = peek_token();
        if (token.type == TOKEN_MUL) {
            next_token();
            value *= parse_factor();
            break;
        } else if (token.type == TOKEN_DIV) {
            next_token();
            value /= parse_factor();
            break;
        } else if (token.type == TOKEN_REMAINDER)  {
            next_token();
            value = fmod(value, parse_factor());
            break;
        } else {
            break;
        }
    }

    return value;
}

float parse_expression() {
    float value = parse_term();
    while (1) {
        Token token = peek_token();
        if (token.type == TOKEN_ADD) {
            next_token();
            value += parse_term();
            break;
        } else if (token.type == TOKEN_SUB) {
            next_token();
            value -= parse_term();
            break;
        } else {
            break;
        }
    }

    return value;
}


