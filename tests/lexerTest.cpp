#include "gtest/gtest.h"
#include "lexer.h"

TEST(lexerTest, simpleReturnTest)
{
    const char* source = "return 3;";
    const auto tokens = Lexer{source}.lex();
    
    EXPECT_EQ(tokens.size(), 3);

    EXPECT_EQ(TokenType::TK_RETURN, tokens[0].type);
    EXPECT_EQ(TokenType::TK_NUM_LITERAL, tokens[1].type);
    EXPECT_EQ(TokenType::TK_SEMICOLON, tokens[2].type);
}

TEST(lexerTest, charLiteralTest)
{
    const char* source = "char x = 'x';";
    const auto tokens = Lexer{source}.lex();

    EXPECT_EQ(5, tokens.size());
    
    EXPECT_EQ(TokenType::TK_CHAR, tokens[0].type);
    
    EXPECT_EQ(TokenType::TK_IDENT, tokens[1].type);
    EXPECT_EQ("x", std::get<std::string_view>(tokens[1].value));

    EXPECT_EQ(static_cast<TokenType>('='), tokens[2].type);

    EXPECT_EQ(TokenType::TK_CHAR_LITERAL, tokens[3].type);
    EXPECT_EQ('x', std::get<char>(tokens[3].value));

    EXPECT_EQ(static_cast<TokenType>(';'), tokens[4].type);
}
