use std::borrow::Borrow;

#[derive(PartialEq)]
pub enum Token {
    LefParen,    // (
    RightParen,  // )
    LeftBrace,   // {
    RightBrace,  // }
    LeftSquare,  // [
    RightSquare, // ]
    Dot,         // .
    Comma,       // ,
    Semicolon,   // ;
    Star,        // *
    Plus,        // +
    Minus,       // -
    Slash,       // /
    Assigment,   // =
    Exclamation, // !
    Tilde,       // ~
    Circumflex,  // ^
    Pipe,        // |
    Ampersand,   // &

    Auto,
    Break,
    Char,
    Continue,
    Case,
    Do,
    Default,
    Const,
    Double,
    Else,
    Enum,
    Extern,
    For,
    If,
    Inline,
    Goto,
    Float,
    Int,
    Long,
    Register,
    Restrict,
    Return,
    Signed,
    Static,
    Sizeof,
    Short,
    Struct,
    Switch,
    Typedef,
    Union,
    Void,
    While,
    Volatile,
    Unsigned,

    Invalid(String),

    Ident(String),
    IntegerNumeral(i32),
}

pub struct LexingResult(pub Vec<Token>);

impl std::fmt::Debug for Token {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Token::LefParen => write!(f, "(")?,
            Token::RightParen => write!(f, ")")?,
            Token::LeftBrace => write!(f, "{{")?,
            Token::RightBrace => write!(f, "}}")?,
            Token::LeftSquare => write!(f, "[")?,
            Token::RightSquare => write!(f, "]")?,
            Token::Dot => write!(f, ".")?,
            Token::Comma => write!(f, ",")?,
            Token::Semicolon => write!(f, ";")?,
            Token::Star => write!(f, "*")?,
            Token::Plus => write!(f, "+")?,
            Token::Minus => write!(f, "-")?,
            Token::Slash => write!(f, "/")?,
            Token::Assigment => write!(f, "=")?,
            Token::Exclamation => write!(f, "!")?,
            Token::Tilde => write!(f, "~")?,
            Token::Circumflex => write!(f, "^")?,
            Token::Pipe => write!(f, "|")?,
            Token::Ampersand => write!(f, "&")?,
            Token::Auto => write!(f, "Keyword: auto")?,
            Token::Break => write!(f, "Keyword: break")?,
            Token::Char => write!(f, "Keyword: char")?,
            Token::Continue => write!(f, "Keyword: continue")?,
            Token::Case => write!(f, "Keyword: case")?,
            Token::Do => write!(f, "Keyword: do")?,
            Token::Default => write!(f, "Keyword: default")?,
            Token::Const => write!(f, "Keyword: const")?,
            Token::Double => write!(f, "Keyword: double")?,
            Token::Else => write!(f, "Keyword: else")?,
            Token::Enum => write!(f, "Keyword: enum")?,
            Token::Extern => write!(f, "Keyword: extern")?,
            Token::For => write!(f, "Keyword: for")?,
            Token::If => write!(f, "Keyword: if")?,
            Token::Inline => write!(f, "Keyword: inline")?,
            Token::Goto => write!(f, "Keyword: goto")?,
            Token::Float => write!(f, "Keyword: float")?,
            Token::Int => write!(f, "Keyword: int")?,
            Token::Long => write!(f, "Keyword: long")?,
            Token::Register => write!(f, "Keyword: register")?,
            Token::Restrict => write!(f, "Keyword: restrict")?,
            Token::Return => write!(f, "Keyword: return")?,
            Token::Signed => write!(f, "Keyword: signed")?,
            Token::Static => write!(f, "Keyword: static")?,
            Token::Sizeof => write!(f, "Keyword: sizeof")?,
            Token::Short => write!(f, "Keyword: short")?,
            Token::Struct => write!(f, "Keyword: struct")?,
            Token::Switch => write!(f, "Keyword: switch")?,
            Token::Typedef => write!(f, "Keyword: typedef")?,
            Token::Union => write!(f, "Keyword: union")?,
            Token::Void => write!(f, "Keyword: void")?,
            Token::While => write!(f, "Keyword: while")?,
            Token::Volatile => write!(f, "Keyword: volatile")?,
            Token::Unsigned => write!(f, "Keyword: unsigned")?,
            Token::Ident(ident) => write!(f, "Ident: {}", ident)?,
            Token::IntegerNumeral(num) => write!(f, "Integer constant: {}", num)?,
            Token::Invalid(ident) => write!(f, "Invalid: '{}'", ident)?,
        }
        
        Ok(())
    }
}

impl std::fmt::Debug for LexingResult {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let LexingResult(tokens) = self;
        writeln!(f, "[")?;
        for i in tokens {
            writeln!(f, "\t{:?}", i)?;
        }
        writeln!(f, "]")?;
        Ok(())
    }
}