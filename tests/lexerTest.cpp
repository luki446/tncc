#include "gtest/gtest.h"
#include "lexer.h"

TEST(lexerTest, simpleReturnTest)
{
    const char* source = "return 3;";
    const auto tokens = Lexer(source).lex();
    
    EXPECT_EQ(tokens.size(), 3);

    EXPECT_EQ(TokenType::TK_RETURN, tokens[0].type);
    EXPECT_EQ(TokenType::TK_NUM_LITERAL, tokens[1].type);
    EXPECT_EQ(TokenType::TK_SEMICOLON, tokens[2].type);
}
