#ifndef TOKEN_HPP
#define TOKEN_HPP


// enum TokenType
// {
//     // Single-character tokens.
//     LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
//     COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
//     AND , OR ,

//     // One or two character tokens.
//     BANG, BANG_EQUAL,
//     EQUAL, EQUAL_EQUAL,
//     GREATER, GREATER_EQUAL,
//     LESS, LESS_EQUAL,

//     // Literals.
//     IDENTIFIER, STRING, NUMBER,

//     // Keywords.
//     CLASS, ELSE, FALSE, FUN, FOR, IF, NIL,
//     PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE
// };

#ifdef X
    #undef X
#endif

#define TOKEN_TYPE_LIST(X) \
    X(LEFT_PAREN)       \
    X(RIGHT_PAREN)      \
    X(LEFT_BRACE)       \
    X(RIGHT_BRACE)      \
    X(COMMA)            \
    X(DOT)              \
    X(MINUS)            \
    X(PLUS)             \
    X(SEMICOLON)        \
    X(SLASH)            \
    X(STAR)             \
    X(AND)              \
    X(OR)               \
    X(BANG)             \
    X(BANG_EQUAL)       \
    X(EQUAL)            \
    X(EQUAL_EQUAL)      \
    X(GREATER)          \
    X(GREATER_EQUAL)    \
    X(LESS)             \
    X(LESS_EQUAL)       \
    X(IDENTIFIER)       \
    X(STRING)           \
    X(NUMBER)           \
    X(IF)               \
    X(ELSE)             \
    X(FOR)              \
    X(WHILE)            \
    X(TRUE)             \
    X(FALSE)            \
    


typedef enum
{
    #define X(n) n,
        TOKEN_TYPE_LIST(X)
    #undef X

    END_OF_FILE
} TokenType;

inline const char* tokenTypeToStr(TokenType token_type)
{

    static const char* token_type_string[] = {
        #define X(n) #n ,
            TOKEN_TYPE_LIST(X)
        #undef X
        
        "END_OF_FILE"
    };


    return token_type_string[(int)token_type];
}


typedef struct Token
{
    const char* strValue;
    double numValue;
    TokenType tokenType;
    int line;
} Token;


#endif