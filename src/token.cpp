#include "token.h"

Token::Token(TokenType type, uint32_t line, uint32_t column, TokenValue value)
    : type(type)
    , value(value)
    , line(line)
    , column(column)
{
}

Token::Token(TokenType type, uint32_t line, uint32_t column)
    : type(type)
    , value("")
    , line(line)
    , column(column)
{
}

auto Token::operator==(const Token& rhs) const -> bool
{
    return type == rhs.type && value == rhs.value;
}

