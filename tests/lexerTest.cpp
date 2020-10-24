#include "lexer.h"
#include "gtest/gtest.h"

TEST(lexerTest, simpleReturnTest)
{
    std::string_view const source = "return 3;";
    auto const tokens = Lexer { source }.lex();

    std::vector<Token> const desiredTokens {
        Token { TokenType::TK_RETURN },
        Token { TokenType::TK_NUM_LITERAL, 3 },
        Token { TokenType::TK_SEMICOLON },
    };

    EXPECT_EQ(desiredTokens, tokens);
}

TEST(lexerTest, charLiteralTest)
{
    std::string_view const source = "char x = 'x';";
    auto const tokens = Lexer { source }.lex();

    std::vector<Token> const desiredTokens {
        Token { TokenType::TK_CHAR },
        Token { TokenType::TK_IDENT, "x" },
        Token { TokenType::TK_ASSIGNMENT },
        Token { TokenType::TK_CHAR_LITERAL, 'x' },
        Token { TokenType::TK_SEMICOLON },
    };

    EXPECT_EQ(desiredTokens, tokens);
}

TEST(lexerTest, stringLiteralTest)
{
    std::string_view const source = "char* x = \"Foo bar\";";
    auto const tokens = Lexer { source }.lex();

    std::vector<Token> const desiredTokens {
        Token { TokenType::TK_CHAR },
        Token { TokenType::TK_STAR },
        Token { TokenType::TK_IDENT, "x" },
        Token { TokenType::TK_ASSIGNMENT },
        Token { TokenType::TK_STRING_LITERAL, "Foo bar" },
        Token { TokenType::TK_SEMICOLON },
    };

    EXPECT_EQ(desiredTokens, tokens);
}