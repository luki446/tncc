#include <fmt/core.h>
#include <fstream>

#include "lexer.h"

int main(int argc, char* argv[])
{
    std::ifstream inputFile(argv[1]);
    std::string const source((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    auto const tokens = Lexer { source }.lex();

    PRINT_DEBUG_TOKENS(tokens)
}