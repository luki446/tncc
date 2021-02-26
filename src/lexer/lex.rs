use super::token::Token;

pub trait Lexer {
    fn from_src(src: String) -> Self;
    fn lex(&mut self) -> Vec<Token>;
}

pub fn lex_source<T: Lexer>(src: String) -> Vec<Token> {
    let mut lexer = T::from_src(src);

    return lexer.lex();
}
