#include "lexer.h"

Lexer::Lexer(std::string_view source)
    : src(source)
{
}

auto Lexer::lex() -> const std::vector<Token>
{
    std::vector<Token> tokens;
    uint32_t currentColumn;

    uint32_t start = position;
    uint32_t length = 0;

    std::string_view rawToken;

    char current;

    while ((current = next()) != '\0') {
        currentColumn = column;
        switch (current) {
        case '(':
        case ')':
        case '{':
        case '}':
        case '[':
        case ']':
        case ',':
        case ';':
            tokens.emplace_back(
                static_cast<TokenType>(current),
                line,
                currentColumn);
            break;
        case '*':
            if (peek() != '=') {
                tokens.emplace_back(
                    static_cast<TokenType>('*'),
                    line,
                    currentColumn);
            }
            break;
        case '=':
            if (peek() != '=') {
                tokens.emplace_back(
                    static_cast<TokenType>('='),
                    line,
                    currentColumn);
            }
            break;
        case '\'':
            start = position;
            length = 0;

            for (auto nextChar = peek(); nextChar != '\''; next(), nextChar = peek()) {
                length++;
            }
            next();
            rawToken = src.substr(start, length);

            switch (rawToken.size()) {
            case 0:
                // TODO: Error handling for empty char constant
            case 1:
                tokens.emplace_back(TokenType::TK_CHAR_LITERAL,
                    line,
                    currentColumn,
                    rawToken[0]);
                break;
            case 2:
                if (rawToken[0] == '\\') {
                    char asciiValue;
                    switch (rawToken[1]) {
                    case 'a':
                        asciiValue = 0x07;
                        break;
                    case 'b':
                        asciiValue = 0x08;
                        break;
                    case 'e':
                        asciiValue = 0x1B;
                        break;
                    case 'f':
                        asciiValue = 0x0C;
                        break;
                    case 'n':
                        asciiValue = 0x0A;
                        break;
                    case 'r':
                        asciiValue = 0x0D;
                        break;
                    case 't':
                        asciiValue = 0x09;
                        break;
                    case 'v':
                        asciiValue = 0x0B;
                        break;
                    case '\\':
                        asciiValue = 0x5C;
                        break;
                    case '\'':
                        asciiValue = 0x27;
                        break;
                    case '\"':
                        asciiValue = 0x22;
                        break;
                    case '?':
                        asciiValue = 0x3F;
                        break;
                        //default:
                        // TODO: Error handling invalid escape characters
                    }
                    tokens.emplace_back(TokenType::TK_CHAR_LITERAL,
                        line,
                        currentColumn,
                        asciiValue);
                } else {
                    // TODO: Error handling for incorrect escape characters
                }
                //default:
                // TODO: Error handling for too long char literal
            }
            break;
        default:
            if (std::isalpha(current) || current == '_') {
                start = position - 1;
                length = 1;
                for (auto nextChar = peek(); std::isalnum(nextChar) || nextChar == '_'; next(), nextChar = peek()) {
                    length++;
                }
                rawToken = src.substr(start, length);

                if (Lexer::keysMap.contains(rawToken)) {
                    tokens.emplace_back(
                        Lexer::keysMap.at(rawToken),
                        line,
                        currentColumn,
                        "");
                } else {
                    tokens.emplace_back(
                        TokenType::TK_IDENT,
                        line,
                        currentColumn,
                        rawToken);
                }

            } else if (std::isdigit(current)) {
                start = position - 1;
                length = 1;

                for (auto nextChar = peek(); std::isdigit(nextChar); next(), nextChar = peek()) {
                    length++;
                }

                rawToken = src.substr(start, length);

                int result = -1234;

                std::from_chars(rawToken.begin(), rawToken.end(), result);

                tokens.emplace_back(
                    TokenType::TK_NUM_LITERAL,
                    line,
                    currentColumn,
                    result);
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
    fmt::print("{}\n", tokens);
}
#endif
