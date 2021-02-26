#[derive(Debug, PartialEq)]
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

    Ident(String),
    IntegerNumeral(i32),
}
