#pragma once

#include <charconv>
#include <cstdlib>
#include <ctype.h>
#include <string>
#include <string_view>
#include <token.h>
#include <unordered_map>
#include <variant>
#include <vector>

#ifdef DEBUG
#define PRINT_DEBUG_TOKENS(x) print_tokens(x);
#include <fmt/core.h>
#else
#define PRINT_DEBUG_TOKENS(x)
#endif

class Lexer {
public:
    explicit Lexer(std::string_view const source);
    auto lex() -> std::vector<Token> const;

private:
    auto next() -> char;
    [[nodiscard]] auto peek() const -> char;

    std::string_view src;
    uint32_t column { 0 };
    uint32_t line { 1 };
    uint32_t position { 0 };

    static std::unordered_map<std::string_view, TokenType> const keysMap;
};

#ifdef DEBUG
void print_tokens(std::vector<Token> const& tokens);
#endif