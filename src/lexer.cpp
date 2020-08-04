#include "lexer.h"

Lexer::Lexer(std::string_view&& source)
    : src(std::move(source))
    , column(0)
    , line(1)
    , position(0)
{
}

auto Lexer::lex() -> const std::vector<Token>
{
    std::vector<Token> tokens;

    char current;

    while ((current = next()) != '\0') {
        switch (current) {
        case '(':
        case ')':
        case '{':
        case '}':
        case '[':
        case ']':
        case ',':
        case ';':
            tokens.push_back({ static_cast<TokenType>(current), "" });
            break;
        case '*':
            if (peek() != '=') {
                tokens.push_back({ static_cast<TokenType>('*'), "" });
            }
            break;
        default:
            if (std::isalpha(current) || current == '_') {
                auto start = position - 1;
                auto length = 1;
                for (auto nextChar = peek(); std::isalnum(nextChar) || nextChar == '_'; next(), nextChar = peek()) {
                    length++;
                }
                const auto ident = src.substr(start, length);

                if (Lexer::keysMap.contains(ident)) {
                    tokens.push_back({ Lexer::keysMap.at(ident), ident });
                } else {
                    tokens.push_back({ TokenType::TK_IDENT, ident });
                }

            } else if (std::isdigit(current)) {
                auto start = position - 1;
                auto length = 1;

                for (auto nextChar = peek(); std::isdigit(nextChar); next(), nextChar = peek()) {
                    length++;
                }

                const auto num = src.substr(start, length);

                tokens.push_back({ TokenType::TK_NUM_LITERAL, num });
            }
        }
    }

    return tokens;
}

auto Lexer::next() -> char
{
    if (src[position] != '\n') {
        column++;
    } else {
        line++;
        column = 1;
    }
    return src[position++];
}

auto Lexer::peek() const -> char
{
    return src[position];
}

const std::unordered_map<std::string_view, TokenType> Lexer::keysMap {
    { "auto", TokenType::TK_AUTO },
    { "break", TokenType::TK_BREAK },
    { "case", TokenType::TK_CASE },
    { "char", TokenType::TK_CHAR },
    { "const", TokenType::TK_CONST },
    { "continue", TokenType::TK_CONTINUE },
    { "default", TokenType::TK_DEFAULT },
    { "do", TokenType::TK_DO },
    { "double", TokenType::TK_DOUBLE },
    { "else", TokenType::TK_ELSE },
    { "enum", TokenType::TK_ENUM },
    { "extern", TokenType::TK_EXTERN },
    { "float", TokenType::TK_FLOAT },
    { "for", TokenType::TK_FOR },
    { "goto", TokenType::TK_GOTO },
    { "if", TokenType::TK_IF },
    { "inline", TokenType::TK_INLINE },
    { "int", TokenType::TK_INT },
    { "long", TokenType::TK_LONG },
    { "register", TokenType::TK_REGISTER },
    { "restrict ", TokenType::TK_RESTRICT },
    { "return", TokenType::TK_RETURN },
    { "short", TokenType::TK_SHORT },
    { "signed", TokenType::TK_SIGNED },
    { "sizeof", TokenType::TK_SIZEOF },
    { "static", TokenType::TK_STATIC },
    { "struct", TokenType::TK_STRUCT },
    { "switch", TokenType::TK_SWITCH },
    { "typedef", TokenType::TK_TYPEDEF },
    { "union", TokenType::TK_UNION },
    { "unsigned", TokenType::TK_UNSIGNED },
    { "void", TokenType::TK_VOID },
    { "volatile", TokenType::TK_VOLATILE },
    { "while", TokenType::TK_WHILE },
    { "_Bool", TokenType::TK_BOOL },
    { "_Complex", TokenType::TK_COMPLEX },
    { "_Imaginary", TokenType::TK_IMAGINARY },
};

#ifdef DEBUG
void print_tokens(const std::vector<Token>& tokens)
{
    for (const auto& tok : tokens) {
        if (tok.value == "") {
            fmt::print("Token: {}\n", static_cast<char>(tok.type));
        } else {
            fmt::print("Token: {}\n", tok.value);
        }
    }
}
#endif
