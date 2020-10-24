#pragma once

#include <fmt/core.h>
#include <string_view>
#include <variant>

enum class TokenType : uint16_t {
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
    TK_ASSIGNMENT = '=',

    TK_EXCLAMATION = '!',
    TK_TILDE = '~',
    TK_CIRCUMFLEX = '^',

    TK_PIPE = '|',
    TK_AMPERSAND = '&',

    TK_LESS = '<',
    TK_MORE = '>',

    TK_IDENT = 256,

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
    TK_STRING_LITERAL,
};

using TokenValue = std::variant<std::string_view, char, int32_t, double>;

struct Token {
    TokenType type;
    TokenValue value;
    uint32_t line;
    uint32_t column;

    Token(TokenType type, uint32_t line, uint32_t column, TokenValue value);
    Token(TokenType type, uint32_t line, uint32_t column);
    #ifdef DEBUG
    Token(TokenType type);
    Token(TokenType type, TokenValue value);
    #endif

    auto operator==(const Token& rhs) const -> bool;
};

#ifdef DEBUG
template <>
struct fmt::formatter<Token> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(Token const& token, FormatContext& ctx)
    {
    switch (token.type) {
    case TokenType::TK_AUTO:
        return fmt::format_to(ctx.out(), "Keyword: auto");
    case TokenType::TK_BREAK:
        return fmt::format_to(ctx.out(), "Keyword: break");
    case TokenType::TK_CONTINUE:
        return fmt::format_to(ctx.out(), "Keyword: continue");
    case TokenType::TK_CASE:
        return fmt::format_to(ctx.out(), "Keyword: case");
    case TokenType::TK_CHAR:
        return fmt::format_to(ctx.out(), "Keyword: char");
    case TokenType::TK_DO:
        return fmt::format_to(ctx.out(), "Keyword: do");
    case TokenType::TK_DEFAULT:
        return fmt::format_to(ctx.out(), "Keyword: default");
    case TokenType::TK_CONST:
        return fmt::format_to(ctx.out(), "Keyword: const");
    case TokenType::TK_DOUBLE:
        return fmt::format_to(ctx.out(), "Keyword: double");
    case TokenType::TK_ELSE:
        return fmt::format_to(ctx.out(), "Keyword: else");
    case TokenType::TK_ENUM:
        return fmt::format_to(ctx.out(), "Keyword: enum");
    case TokenType::TK_EXTERN:
        return fmt::format_to(ctx.out(), "Keyword: extern");
    case TokenType::TK_FOR:
        return fmt::format_to(ctx.out(), "Keyword: for");
    case TokenType::TK_IF:
        return fmt::format_to(ctx.out(), "Keyword: if");
    case TokenType::TK_INLINE:
        return fmt::format_to(ctx.out(), "Keyword: inline");
    case TokenType::TK_GOTO:
        return fmt::format_to(ctx.out(), "Keyword: goto");
    case TokenType::TK_FLOAT:
        return fmt::format_to(ctx.out(), "Keyword: float");
    case TokenType::TK_INT:
        return fmt::format_to(ctx.out(), "Keyword: int");
    case TokenType::TK_LONG:
        return fmt::format_to(ctx.out(), "Keyword: long");
    case TokenType::TK_REGISTER:
        return fmt::format_to(ctx.out(), "Keyword: register");
    case TokenType::TK_RESTRICT:
        return fmt::format_to(ctx.out(), "Keyword: restrict");
    case TokenType::TK_RETURN:
        return fmt::format_to(ctx.out(), "Keyword: return");
    case TokenType::TK_SIGNED:
        return fmt::format_to(ctx.out(), "Keyword: signed");
    case TokenType::TK_STATIC:
        return fmt::format_to(ctx.out(), "Keyword: static");
    case TokenType::TK_SIZEOF:
        return fmt::format_to(ctx.out(), "Keyword: sizeof");
    case TokenType::TK_SHORT:
        return fmt::format_to(ctx.out(), "Keyword: short");
    case TokenType::TK_STRUCT:
        return fmt::format_to(ctx.out(), "Keyword: struct");
    case TokenType::TK_SWITCH:
        return fmt::format_to(ctx.out(), "Keyword: switch");
    case TokenType::TK_TYPEDEF:
        return fmt::format_to(ctx.out(), "Keyword: typedef");
    case TokenType::TK_UNION:
        return fmt::format_to(ctx.out(), "Keyword: union");
    case TokenType::TK_VOID:
        return fmt::format_to(ctx.out(), "Keyword: void");
    case TokenType::TK_WHILE:
        return fmt::format_to(ctx.out(), "Keyword: while");
    case TokenType::TK_VOLATILE:
        return fmt::format_to(ctx.out(), "Keyword: volatile");
    case TokenType::TK_UNSIGNED:
        return fmt::format_to(ctx.out(), "Keyword: unsigned");
    case TokenType::TK_BOOL:
        return fmt::format_to(ctx.out(), "Keyword: _Bool");
    case TokenType::TK_COMPLEX:
        return fmt::format_to(ctx.out(), "Keyword: _Complex");
    case TokenType::TK_IMAGINARY:
        return fmt::format_to(ctx.out(), "Keyword: _Imaginary");
    case TokenType::TK_CHAR_LITERAL:
        return fmt::format_to(ctx.out(), "Char literal: '{}'", std::get<char>(token.value));
    case TokenType::TK_NUM_LITERAL:
        return fmt::format_to(ctx.out(), "Integer literal: {}", std::get<int32_t>(token.value));
    case TokenType::TK_STRING_LITERAL:
        return fmt::format_to(ctx.out(), "String literal: \"{}\"", std::get<std::string_view>(token.value));
    case TokenType::TK_IDENT:
        return fmt::format_to(ctx.out(), "Identifier: {}", std::get<std::string_view>(token.value));
    default:
        if (int tokenNum = static_cast<int>(token.type); tokenNum > 31 && tokenNum < 128) {
            return fmt::format_to(ctx.out(), "Symbol: '{}'", static_cast<char>(tokenNum));
        } else {
            return fmt::format_to(ctx.out(), "Token {0:#x} cannot be printed", tokenNum);
        }
    }
}
};

template <>
struct fmt::formatter<std::vector<Token>> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(std::vector<Token> const& tokens, FormatContext& ctx)
    {
        if (tokens.size() == 0) {
            return fmt::format_to(ctx.out(), "{{}}");
        }

        fmt::format_to(ctx.out(), "{{\n");
        for (auto const& tok : tokens) {
            fmt::format_to(ctx.out(), "\t{},\n", tok);
        }
        return fmt::format_to(ctx.out(), "}}");
    }
};
#endif
