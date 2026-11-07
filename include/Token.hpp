#ifndef TOKEN_HPP
#define TOKEN_HPP


enum TokenType
{
    // Single-character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
    AND , OR ,

    // One or two character tokens.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals.
    IDENTIFIER, STRING, NUMBER,

    // Keywords.
    CLASS, ELSE, FALSE, FUN, FOR, IF, NIL,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE
};

typedef struct Token
{
    const char* strValue;
    double numValue;
    TokenType tokenType;
    int line;
} Token;


#endif