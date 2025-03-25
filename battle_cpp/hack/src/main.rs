mod challenge;

use challenge::Challenge;
use std::time::Duration;
use std::task::Poll;
use colored::Colorize;

#[tokio::main]
async fn main() {   
    const TIMER: u64 = 30; // May be modified to ease or harden the challenge

    let mut challenge = Challenge::new(TIMER);
    challenge.print_instruction();

    let mut timer = std::pin::pin!(tokio::time::sleep(Duration::from_secs(TIMER)));

    loop {
        let poll = challenge.routine().await;
        if let Poll::Ready(()) = libp2p::futures::poll!(&mut timer) {
            println!("{}", "\n\rThe security breach closed too soon...\r".red());
            return;
        }  else if let Poll::Ready(b) = poll {
            if b { println!("{}", "\rHack's successful\r".green()) }
            else { println!("{}", "\rHack has failed !\r".red()) }
            return;
        }
    }
}

