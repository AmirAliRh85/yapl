#include "../include/Scanner.hpp"

#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)

const std::unordered_map<const char* , TokenType> tokens = {
    {"if" , IF},
    {"else" , ELSE},
    {"for" , FOR},
    {"while" , WHILE},
    {"true" , TRUE},
    {"false" , FALSE},
};


Scanner::Scanner(const char* file_path , const unsigned int buffer_size)
{
    filePath = file_path;
    source = NULL;

    start = 0;
    current = 0;
    line = 1;
}

Scanner::Scanner(const char* file_path)
{
    filePath = file_path;
    source = NULL;
    
    start = 0;
    current = 0;
    line = 1;
}

void Scanner::openFileAll()
{
    FILE* file = fopen(filePath , "r");
    
    if (!file)
    {
        printf("[ERROR] Failed to read file\n");
        return;
    }

    fseek(file , 0 , SEEK_END);
    bufferSize = ftell(file);
    rewind(file);

    source = (char*)malloc(sizeof(char) * (bufferSize + 1));

    size_t got = fread(source , 1 , bufferSize , file);
    source[got] = '\0';

    fclose(file);
}


std::vector<Token>* Scanner::generateToken()
{
    openFileAll();

    if (source == NULL)
    {
        printf("[ERROR] Failed to retrieve the source file\n");
        return NULL;
    }

    while (!isAtEnd())
    {
        start = current;
        scanToken();
    }

    addToken(END_OF_FILE);

    for (Token t : tokens)
    {
        printf("%i | %.1f , %s , %s\n" , t.line , t.numValue , t.strValue , tokenTypeToStr(t.tokenType));
    }

    return &tokens;
}

void Scanner::scanToken()
{
    char c = advance();

    switch (c)
    {
        case '(' : addToken(LEFT_PAREN); break;
        case ')' : addToken(RIGHT_PAREN); break;
        case '{' : addToken(LEFT_BRACE); break;
        case '}' : addToken(RIGHT_BRACE); break;
        case ',' : addToken(COMMA); break;
        case '.' : addToken(DOT); break;
        case '-' : addToken(MINUS); break;
        case '+' : addToken(PLUS); break;
        case ';' : addToken(SEMICOLON); break;
        case '*' : addToken(STAR); break;

        case '!' :
            if (peek() == '=')
            {
                addToken(BANG_EQUAL);
                advance();
            }
            else
            {
                addToken(BANG);
            }
            break;

        case '=' :
            if (peek() == '=')
            {
                addToken(EQUAL_EQUAL);
                advance();
            }
            else
            {
                addToken(EQUAL);
            }
            break;

        case '<' :
            if (peek() == '=')
            {
                addToken(LESS_EQUAL);
                advance();
            }
            else
            {
                addToken(LESS);
            }
            break;

        case '>' :
            if (peek() == '=')
            {
                addToken(GREATER_EQUAL);
                advance();
            }
            else
            {
                addToken(GREATER);
            }
            break;

        case ' ' : break;
        case '\t' : break;
        case '\r' : break;

        case '\n' :
            line++;
            break;

        case '/' :
            if (peek(1) == '/')
            {
                while (peek(0) != '\n' && !isAtEnd())
                    advance();
            }
            else
            {
                addToken(SLASH);
            }

        default :
            if (isDigit(c))
            {
                number();
            }
            else if (c == '"')
            {
                string();
            }
            else
                break;

    }
}

char Scanner::peek(int n)
{
    return source[current + n];
}

char Scanner::advance()
{
    return source[current++];
}

bool Scanner::isAtEnd()
{
    return current >= bufferSize;
}

bool Scanner::isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool Scanner::isAlphaNumeric(char c)
{
    return isDigit(c) || isAlpha(c);
}

bool Scanner::isWhitespace(char c)
{
    return c == '\n' || c == ' ' || c == '\t' || c == '\r';
}

void Scanner::number()
{
    bool has_left_side = false;
    bool is_float = false;
    bool has_right_side = false;

    char num[64];
    int idx = 0;

    num[idx++] = peek(-1);

    while (isDigit(peek()))
    {
        num[idx++] = peek();
        advance();
        has_left_side = true;
    }

    if (peek() == '.')
    {
        num[idx++] = '.';
        advance();
        is_float = true;

        while (isDigit(peek()))
        {
            num[idx++] = peek();
            advance();
            has_right_side = true;
        }
    }

    num[idx] = '\0';

    addToken(NUMBER , NULL , std::atof(num));   
}

void Scanner::string()
{
    return;
}

void Scanner::addToken(TokenType token_type , const char* str_val , double val)
{
    tokens.push_back((Token){str_val , val , token_type , line});
}