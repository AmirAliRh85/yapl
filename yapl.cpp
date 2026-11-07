#include "./YAPL.hpp"
#include <stdio.h>

void interpretFile(const char* file_path)
{
    Scanner scanner(file_path);
    std::vector<Token>* tokens = scanner.scanToken();
}

int main(int argc , char* argv[])
{
    if (argc <= 1)
    {
        printf("Usage: yapl [filename.japl]");
        return 1;
    }
    else if (argc == 2)
    {
        interpretFile(argv[argc - 1]);
    }
    else
    {
        printf("yapl compiler does not support flags");
    }
}