use std::io::{stdout, StdoutLock, Read, Write, Bytes};
use std::task::Poll;
use colored::Colorize;
use termion::{async_stdin, AsyncReader};

use termion::raw::{IntoRawMode, RawTerminal};

pub struct Challenge {
    stdout: RawTerminal<StdoutLock<'static>>,
    stdin: Bytes<AsyncReader>,
    timer: u64,
    adress: String,
    prompt: String,
}

impl Challenge {
    fn generate_random_adress() -> String {
        let bytes = vec!['1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'];
        let mut res = String::from("0x");
        for _ in 0..6 {
            let i: u8 = rand::random();
            let i = i as usize % bytes.len();
            res.push(bytes[i]);
        };

        res
    }

    fn assert_prompt(&self) -> bool {
        let correct = format!("int* boss_hp = {}; *boss_hp -= 500;", self.adress);
        return self.prompt == correct
    }

    pub fn new(timer: u64) -> Self {
        let stdin = async_stdin().bytes();
        let mut stdout = stdout().lock().into_raw_mode().unwrap();
        let adress = Challenge::generate_random_adress();

        write!(stdout, "{}{}", termion::clear::All, termion::cursor::Goto(1, 1)).unwrap();  
        Self {stdin, stdout, timer, adress, prompt: String::new()}
    }

    pub fn print_instruction(&mut self) {
        println!("{}{}{}", "\rThe adress of the boss hitpoints is located at ".italic(), self.adress.italic().bold(), " !\n".italic());
        println!("{}", "\rPrompt the following command :".italic());
        println!("{}{}{}", "\r\tint* boss_hp = ".italic().yellow(), self.adress.italic().yellow(), "; *boss_hp -= 500;".italic().yellow());
        println!("{}{}{}", "\rNote that you only have ".bold(), self.timer.to_string().bold(), " seconds, starting from now !\r\n".bold());
        write!(self.stdout, "\r> ").unwrap();
        self.stdout.flush().unwrap();
    }

    pub async fn routine(&mut self) -> Poll<bool> {
        let b = self.stdin.next();
        if let Some(Ok(byte)) = b {
            match byte {
                b'\r' => {
                    println!();
                    return Poll::Ready(self.assert_prompt());
                },
                127 => {
                    self.prompt.pop();
                    write!(self.stdout, "{}{}", termion::clear::All, termion::cursor::Goto(1, 1)).unwrap();    
                    self.print_instruction();
                    write!(self.stdout, "\r> {}", self.prompt).unwrap();
                    self.stdout.flush().unwrap();
                }
                _ => {
                    let byte = byte as char;
                    self.prompt.push(byte);
                    write!(self.stdout, "{byte}").unwrap();
                    self.stdout.flush().unwrap();
                }
            }
        }
        return Poll::Pending;
    }
}