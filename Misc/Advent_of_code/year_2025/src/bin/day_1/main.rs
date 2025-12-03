// Day 1: Secret Entrance

use std::{fs::File, io::{BufRead, BufReader}, vec};

// Part 1
const INPUT_PATH: &str  = "./src/bin/day_1/input";
const N_DIALS: u32      = 100;
const DEFAULT_DIAL: u32 = 50;

fn parse_movement(movement: String) -> i16 {
    let mut output = 1;
    output *= if movement.starts_with('L') { 1 } else { -1 };
    output *= movement[1 .. ].parse::<i16>().unwrap();

    return output;
}

fn read_numbers() -> Vec<i16> {
    let mut output: Vec<i16> = vec![];
    output.reserve(1_000);

    let file   = File::open(INPUT_PATH).unwrap();
    let buffer = BufReader::new(file);
    
    for line in buffer.lines() {
        let line = line.unwrap();
        let line = parse_movement(line);

        output.push(line);
    }

    output.shrink_to_fit();
    return output;
}

fn get_first_password(sequence: &Vec<i16>) -> u32 {
    let mut output: u32 = 0;
    let mut dial: i16   = DEFAULT_DIAL as i16;
    
    for i in sequence {
        dial = (dial + i) % (N_DIALS as i16);

        if dial == 0 {
            output += 1;
        }
    }

    return output;
}

// Part 2
fn get_second_password(sequence: &Vec<i16>) -> u32 {
    let mut output: u32 = 0;
    let mut dial: i16   = DEFAULT_DIAL as i16;

    for i in sequence {
        let a = dial + i;
        let b = a / (N_DIALS as i16);
        let b = b.unsigned_abs() as u32;

        output += b;

        if a <= 0 && dial > 0 {
            output += 1;
        }

        dial = a % (N_DIALS as i16);
    }

    return output;
}

fn main() {
    let sequence = read_numbers();
    let answer   = get_first_password(&sequence);

    println!("Part 1 answer: {}", answer);

    let answer = get_second_password(&sequence);

    println!("Part 2 answer: {}", answer);
}