#include "../include/Scanner.hpp";

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
    // bufferSize = buffer_size;

    start = 0;
    current = 0;
    line = 1;
}

Scanner::Scanner(const char* file_path)
{
    filePath = file_path;
    // bufferSize = MAX_BUFFER_SIZE;
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
        printf("Failed to read file\n");
        return;
    }

    fseek(file , 0 , SEEK_END);
    bufferSize = ftell(file);
    rewind(file);

    source = (char*)malloc(sizeof(char) * (bufferSize + 1));

    size_t got = fread(source , 1 , bufferSize , file);
    source[got] = '\0';

    fclose(file);

    printf(source);
}


std::vector<Token>* Scanner::generateToken()
{
    while (isAtEnd())
    {
        start = current;
        scanToken();
    }
}

void Scanner::scanToken()
{
    char c = advance();

    switch (c)
    {
        case '(' : addToken(LEFT_PAREN); break;
        case ')' : addToken(RIGHT_BRACE); break;
        case '{' : addToken(LEFT_BRACE); break;
        case '}' : addToken(RIGHT_BRACE); break;
        case ',' : addToken(COMMA); break;
        case '.' : addToken(DOT); break;
        case '-' : addToken(MINUS); break;
        case '+' : addToken(PLUS); break;
        case ';' : addToken(SEMICOLON); break;
        case '*' : addToken(STAR); break;

        case '!' :
            if (peek(1) == '=')
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
            if (peek(1) == '=')
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
            if (peek(1) == '=')
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
            if (peek(1) == '=')
            {
                addToken(GREATER_EQUAL);
                advance();
            }
            else
            {
                addToken(GREATER);
            }
            break;

        

    }
}

char Scanner::peek(int n)
{
    return source[current + n];
}

char Scanner::advance()
{
    source[current++];
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

void Scanner::addToken(TokenType token_type)
{
    tokens.push_back((Token){NULL , 0 , token_type , line});
}