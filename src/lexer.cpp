#include "lexer.h"

Lexer::Lexer(std::string_view source)
    : src(source)
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

                auto type = TokenType::TK_IDENT;

                // clang-format off
                KEYWORD("auto", TK_AUTO)
                else KEYWORD("break", TK_BREAK)
                else KEYWORD("case", TK_CASE)
                else KEYWORD("char", TK_CHAR)
                else KEYWORD("continue", TK_CONTINUE)
                else KEYWORD("do", TK_DO)
                else KEYWORD("default", TK_DEFAULT)
                else KEYWORD("const", TK_CONST)
                else KEYWORD("double", TK_DOUBLE)
                else KEYWORD("else", TK_ELSE)
                else KEYWORD("enum", TK_ENUM)
                else KEYWORD("extern", TK_EXTERN)
                else KEYWORD("for", TK_FOR)
                else KEYWORD("if", TK_IF)
                else KEYWORD("goto", TK_GOTO)
                else KEYWORD("float", TK_FLOAT)
                else KEYWORD("int", TK_INT)
                else KEYWORD("long", TK_LONG)
                else KEYWORD("register", TK_REGISTER)
                else KEYWORD("return", TK_RETURN)
                else KEYWORD("signed", TK_SIGNED)
                else KEYWORD("static", TK_STATIC)
                else KEYWORD("sizeof", TK_SIZEOF)
                else KEYWORD("short", TK_SHORT)
                else KEYWORD("struct", TK_STRUCT)
                else KEYWORD("switch", TK_SWITCH)
                else KEYWORD("union", TK_UNION)
                else KEYWORD("void", TK_VOID)
                else KEYWORD("while", TK_WHILE)
                else KEYWORD("volatile", TK_VOLATILE)
                else KEYWORD("unsigned", TK_UNSIGNED)

                tokens.push_back({ type, ident });
                // clang-format on
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

#ifdef DEBUG
void print_tokens(const std::vector<Token>& tokens)
{
    for (auto tok : tokens) {
        if (tok.value == "") {
            fmt::print("Token: {}\n", static_cast<char>(tok.type));
        } else {
            fmt::print("Token: {}\n", tok.value);
        }
    }
}
#endif
