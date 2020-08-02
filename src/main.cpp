#include <fmt/core.h>
#include <fstream>

#include "lexer.h"

int main(int argc, char* argv[])
{
    std::ifstream inputFile(argv[1]);
    std::string source((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    const auto tokens = Lexer(source).lex();

    PRINT_DEBUG_TOKENS(tokens)
}