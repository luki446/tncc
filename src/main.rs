mod cli;
mod lexer;

use lexer::lex::*;
use lexer::regex::RegexLexer;
use std::fs;

use structopt::StructOpt;

fn main() {
    let opt = cli::Opt::from_args();

    let source = fs::read_to_string(opt.file).unwrap();

    let tokens = lex_source::<RegexLexer>(source.clone());

    if opt.dump_lexer {
        println!("{:#?}", tokens);
    } else {
        println!("{}", source);
    }
}
