use std::path::PathBuf;
use structopt::StructOpt;

#[derive(StructOpt, Debug)]
#[structopt(
    name = "Totally Not C Compiler",
    about = "Simple ANSI C compiler written in Rust."
)]
pub struct Opt {
    /// Dump lexer output
    #[structopt(long)]
    pub dump_lexer: bool,

    /// File to compile
    #[structopt(parse(from_os_str))]
    pub file: PathBuf,
}
