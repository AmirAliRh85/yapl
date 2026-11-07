#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <vector>
#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include "./Token.hpp"

#define MAX_BUFFER_SIZE 4096

extern const std::unordered_map<const char* , TokenType> keywords;

class Scanner
{
    private :
        static const std::unordered_map<const char* , TokenType> keywords;

        const char* filePath;
        unsigned int bufferSize;
        char* source;
        std::vector<Token> tokens;

        int start;
        int current;
        int line;

        void openFileAll();
        void openFileBuffer();

        char peek(int n);

        char advance();
        bool isAtEnd();

        bool isDigit(char c);
        bool isAlpha(char c);
        bool isAlphaNumeric(char c);

        void addToken(TokenType token_type);

        void scanToken();

    public :
        Scanner(const char* file_path , const unsigned int buffer_size);
        Scanner(const char* file_path);
        
        std::vector<Token>* generateToken();
};

#endif