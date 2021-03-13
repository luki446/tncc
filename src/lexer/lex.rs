use super::token::Token;

pub trait Lexer {
    fn from_src(src: String) -> Self;
    fn lex(&mut self) -> Result<Vec<Token>, Box<dyn std::error::Error>>;
}

pub fn lex_source<T: Lexer>(src: String) -> Result<Vec<Token>, Box<dyn std::error::Error>> {
    let mut lexer = T::from_src(src);

    return lexer.lex();
}
