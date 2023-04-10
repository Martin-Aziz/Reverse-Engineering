use solveme::Executer;
use std::{
    io::{Write},
    process::{Command, Stdio},
};

fn main() {
    let exec = Executer::new(
        "./crack".into(),
        Some(&do_something),
    );
    exec.go().unwrap();
}

fn do_something(exec: Executer) -> () {
    let mut cmd = Command::new(exec.program_name);
    let mut runner = cmd
        .stdin(Stdio::piped())
        .stdout(Stdio::inherit())
        .spawn()
        .expect("Failed to spawn child process");

    let mut stdin = runner.stdin.take().expect("Failed to open stdin");
    std::thread::spawn(move || {
        stdin
            .write_all(&[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x2f,0x1d,0x40])
            .expect("Failed to write to stdin");
    });

   let output = runner.wait_with_output().expect("Failed to read stdout");

   println!("{}", String::from_utf8_lossy(&output.stdout));
}
