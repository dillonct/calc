#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"
#include <string.h>

static float parse_expression();
static float parse_term();
static float parse_factor();
static void match_token(TokenType type);
static void report_error(const char* msg, int index);

float parse_result() {
    float result = parse_expression();
    match_token(TOKEN_EOL);

    return result;
}

static float parse_expression() {
    float value = parse_term();
    while (1) {
        Token token = peek_token();
        if (token.type == TOKEN_ADD) {
            next_token();
            value += parse_term();
        } else if (token.type == TOKEN_SUB) {
            next_token();
            value -= parse_term();
        } else {
            break;
        }
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
        } else if (token.type == TOKEN_DIV) {
            next_token();
            value /= parse_factor();
        } else if (token.type == TOKEN_REMAINDER)  {
            next_token();
            value = fmod(value, parse_factor());
        } else {
            break;
        }
    }

    return value;
}

static float parse_factor() {
    float value = 0;
    Token token = peek_token();

    if (token.type == TOKEN_NUMBER) {
        next_token();
        char str_slice[token.length + 1]; // include the null terminator
        strncpy(str_slice, token.start, token.length);
        str_slice[token.length] = '\0';
        value = atof(str_slice);
    } else if (token.type == TOKEN_OPEN_PAREN) {
        next_token();
        value = parse_expression();
        match_token(TOKEN_CLOSE_PAREN);
    } else if (token.type == TOKEN_ERROR) {
        // unknown token found
        report_error("Invalid character(s) found at:", token.start - get_input());
        exit(-1);
    }

    return value;
}

static void match_token(TokenType type) {
    if (next_token().type != type) {
        report_error("Missing a character", 0);
        exit(-1);
    }
}

static void report_error(const char* msg, int index) {
    fprintf(stderr, "[ERROR] %s\n", msg);
    fprintf(stderr, "        ");
    fprintf(stderr, "%s\n", get_input());
    if (index != 0) {
        fprintf(stderr, "        ");
        for (int i = 0; i < index - 1; i++) {
            fprintf(stderr, " ");
        }
        fprintf(stderr, "^\n");
    }
}
