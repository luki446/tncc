#include "lexer.h"
#include "gtest/gtest.h"

TEST(lexerTest, simpleReturnTest)
{
    const char* source = "return 3;";
    const auto tokens = Lexer { source }.lex();

    const std::vector<Token> desiredTokens {
        Token { TokenType::TK_RETURN, 0, 0 },
        Token { TokenType::TK_NUM_LITERAL, 0, 0, 3 },
        Token { TokenType::TK_SEMICOLON, 0, 0 },
    };

    EXPECT_EQ(desiredTokens, tokens);
}

TEST(lexerTest, charLiteralTest)
{
    const char* source = "char x = 'x';";
    const auto tokens = Lexer { source }.lex();

    const std::vector<Token> desiredTokens {
        Token { TokenType::TK_CHAR, 0, 0 },
        Token { TokenType::TK_IDENT, 0, 0, "x" },
        Token { TokenType::TK_ASSIGNMENT, 0, 0 },
        Token { TokenType::TK_CHAR_LITERAL, 0, 0, 'x' },
        Token { TokenType::TK_SEMICOLON, 0, 0 },
    };

    EXPECT_EQ(desiredTokens, tokens);
}

TEST(lexerTest, stringLiteralTest)
{
    const char* source = "char* x = \"Foo bar\";";
    const auto tokens = Lexer { source }.lex();

    const std::vector<Token> desiredTokens {
        Token { TokenType::TK_CHAR, 0, 0 },
        Token { TokenType::TK_STAR, 0, 0 },
        Token { TokenType::TK_IDENT, 0, 0, "x" },
        Token { TokenType::TK_ASSIGNMENT, 0, 0 },
        Token { TokenType::TK_STRING_LITERAL, 0, 0, "Foo bar"},
        Token { TokenType::TK_SEMICOLON, 0, 0},
    };

    EXPECT_EQ(desiredTokens, tokens);
}