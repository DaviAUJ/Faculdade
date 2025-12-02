use std::{fs::File, io::{BufRead, BufReader}, vec};

const INPUT_PATH: &str = "./src/bin/teste.txt";

fn read_numbers() -> Vec<i8> {
    let mut output: Vec<i8> = vec![0; 1_000];

    let file = File::open(INPUT_PATH).unwrap();
    let buffer = BufReader::new(file);
    
    for line in buffer.lines() {
        let line = line.unwrap();

        println!("{} - {}", line, line.len());
    }

    return output;
}

fn main() {
    read_numbers();
}