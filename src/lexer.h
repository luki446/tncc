#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <ctype.h>

#define KEYWORD(x, y) if(ident == x)\
type = TokenType::y;\

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
    TK_GOTO,
    TK_FLOAT,
    TK_INT,
    TK_LONG,
    TK_REGISTER,
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

    TK_NUM_LITERAL,
};

struct Token {
    TokenType type;
    std::string_view value;
};

class Lexer {
public:
    explicit Lexer(std::string_view source);
    auto lex() -> const std::vector<Token>;

private:
    auto next() -> char;
    [[nodiscard]] auto peek() const -> char;

    uint32_t column;
    uint32_t line;
    uint32_t position;
    std::string_view src;
};

#ifdef DEBUG
void print_tokens(const std::vector<Token>& tokens);
#endif