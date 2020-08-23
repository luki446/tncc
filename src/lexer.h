#pragma once

#include <cstdlib>
#include <ctype.h>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>


#ifdef DEBUG
#define PRINT_DEBUG_TOKENS(x) print_tokens(x);
#include <fmt/core.h>
#else
#define PRINT_DEBUG_TOKENS(x)
#endif

enum class TokenType {
    TK_LEFT_PAREN = '(',
    TK_RIGHT_PAREN = ')',

    TK_LEFT_BRACE = '{',
    TK_RIGHT_BRACE = '}',

    TK_LEFT_SQUARE = '[',
    TK_RIGHT_SQUARE = ']',

    TK_DOT = '.',
    TK_COMMA = ',',
    TK_SEMICOLON = ';',
    TK_STAR = '*',
    TK_PLUS = '+',
    TK_MINUS = '-',
    TK_SLASH = '/',

    TK_IDENT = 0,

    TK_AUTO,
    TK_BREAK,
    TK_CONTINUE,
    TK_CASE,
    TK_CHAR,
    TK_DO,
    TK_DEFAULT,
    TK_CONST,
    TK_DOUBLE,
    TK_ELSE,
    TK_ENUM,
    TK_EXTERN,
    TK_FOR,
    TK_IF,
    TK_INLINE,
    TK_GOTO,
    TK_FLOAT,
    TK_INT,
    TK_LONG,
    TK_REGISTER,
    TK_RESTRICT,
    TK_RETURN,
    TK_SIGNED,
    TK_STATIC,
    TK_SIZEOF,
    TK_SHORT,
    TK_STRUCT,
    TK_SWITCH,
    TK_TYPEDEF,
    TK_UNION,
    TK_VOID,
    TK_WHILE,
    TK_VOLATILE,
    TK_UNSIGNED,

    TK_BOOL,
    TK_COMPLEX,
    TK_IMAGINARY,

    TK_NUM_LITERAL,
    TK_CHAR_LITERAL,
};

using TokenValue = std::variant<std::string_view, char, uint64_t, double>;

struct Token {
    TokenType type;
    TokenValue value;
    uint32_t line;
    uint32_t column;

    Token(TokenType type, uint32_t line, uint32_t column, TokenValue value);
    Token(TokenType type, uint32_t line, uint32_t column);
};

class Lexer {
public:
    explicit Lexer(std::string_view&& source);
    auto lex() -> const std::vector<Token>;

private:
    auto next() -> char;
    [[nodiscard]] auto peek() const -> char;

    std::string_view src;
    uint32_t column { 0 };
    uint32_t line { 1 };
    uint32_t position { 0 };

    static const std::unordered_map<std::string_view, TokenType> keysMap;
};

#ifdef DEBUG
void print_tokens(const std::vector<Token>& tokens);
#endif