pub mod lex;
pub mod regex;
pub mod token;

#[cfg(test)]
mod tests {
    use super::{lex::lex_source, token::Token,regex::RegexLexer};

    #[test]
    fn basic_return_expr_regex_lexer() {
        let tokens = lex_source::<RegexLexer>("return 3;".to_string()).unwrap();

        assert_eq!(vec![
            Token::Return,
            Token::IntegerNumeral(3),
            Token::Semicolon
        ], tokens);
    }

    #[test]
    fn basic_function_prototype_regex_lexer() {
        let tokens = lex_source::<RegexLexer>("void foo(    int *a, char b[]);".to_string()).unwrap();

        assert_eq!(vec![
            Token::Void,
            Token::Ident("foo".to_string()),
            Token::LefParen,
            Token::Int,
            Token::Star,
            Token::Ident("a".to_string()),
            Token::Comma,
            Token::Char,
            Token::Ident("b".to_string()),
            Token::LeftSquare,
            Token::RightSquare,
            Token::RightParen,
            Token::Semicolon
        ],tokens)
    }
}