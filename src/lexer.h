#ifndef lexer_h
#define lexer_h

typedef enum {
    TOKEN_OPEN_PAREN, TOKEN_CLOSE_PAREN,
    TOKEN_ADD, TOKEN_SUB,
    TOKEN_MUL, TOKEN_DIV,
    TOKEN_REMAINDER,

    TOKEN_NUMBER,

    TOKEN_ERROR, TOKEN_EOL
} TokenType;

typedef struct {
    TokenType type;
    float number;
} Token;

void init_lexer(const char* input);
Token next_token();
Token peek_token();
#endif
