#include "gtest/gtest.h"
#include "lexer.h"

TEST(lexerTest, simpleReturnTest)
{
    const char* source = "return 3;";
    const auto tokens = Lexer(source).lex();
    
    EXPECT_EQ(tokens.size(), 3);

    EXPECT_EQ(tokens[0].type, TokenType::TK_RETURN);
    EXPECT_EQ(tokens[1].type, TokenType::TK_NUM_LITERAL);
    EXPECT_EQ(tokens[2].type, TokenType::TK_SEMICOLON);
}
