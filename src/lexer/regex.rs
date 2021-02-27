use super::lex::Lexer;
use super::token::Token;
use regex::Regex;

pub struct RegexLexer {
    source: String,
}

impl Lexer for RegexLexer {
    fn from_src(src: String) -> Self {
        RegexLexer { source: src }
    }

    fn lex(&mut self) -> Vec<Token> {
        let mut tokens = Vec::new();

        let tokens_re = Regex::new(concat!(
            r"(?P<ident>[a-zA-Z_]+)|",
            r"(?P<number>[0-9]+)|",
            r"(?P<comma>,)|",
            r"(?P<lparen>\()|",
            r"(?P<rparen>\))|",
            r"(?P<lsquare>\[)|",
            r"(?P<rsquare>\])|",
            r"(?P<lbrace>\{)|",
            r"(?P<rbrace>\})|",
            r"(?P<star>\*)|",
            r"(?P<semicolon>;)"
        ))
        .unwrap();

        for cap in tokens_re.captures_iter(self.source.as_str()) {
            let token = if cap.name("ident").is_some() {
                match cap.name("ident").unwrap().as_str() {
                    "int" => Token::Int,
                    "return" => Token::Return,
                    "char" => Token::Char,
                    ident => Token::Ident(ident.to_string()),
                }
            } else if cap.name("number").is_some() {
                match cap.name("number").unwrap().as_str().parse() {
                    Ok(number) => Token::IntegerNumeral(number),
                    Err(_) => panic!("Failed to parse number"),
                }
            } else if cap.name("lparen").is_some() {
                Token::LefParen
            } else if cap.name("rparen").is_some() {
                Token::RightParen
            } else if cap.name("lbrace").is_some() {
                Token::LeftBrace
            } else if cap.name("rbrace").is_some() {
                Token::RightBrace
            } else if cap.name("lsquare").is_some() {
                Token::LeftSquare
            } else if cap.name("rsquare").is_some() {
                Token::RightSquare
            } else if cap.name("star").is_some() {
                Token::Star
            } else if cap.name("comma").is_some() {
                Token::Comma
            } else if cap.name("semicolon").is_some() {
                Token::Semicolon
            } else {
                Token::Ampersand
            };

            tokens.push(token);
        }

        tokens
    }
}
