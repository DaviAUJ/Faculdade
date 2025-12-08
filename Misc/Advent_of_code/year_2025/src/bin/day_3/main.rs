// 3° dia: Lobby

use std::{fs::File, io::{BufRead, BufReader}};

const _TEST_PATH: &str = "./src/bin/day_3/test";
const _INPUT_PATH: &str = "./src/bin/day_3/input";

// Parte 1
fn read_batteries(name: &str) -> Vec<Vec<u8>> {
    let mut out: Vec<Vec<u8>> = Vec::new();
    out.reserve(1_000);

    let file   = File::open(name).unwrap();
    let buffer = BufReader::new(file);

    for line in buffer.lines() {
        let nums: Vec<u8> = line
            .unwrap()
            .chars()
            .map(|c| c.to_digit(10).unwrap() as u8)
            .collect();

        out.push(nums);
    }

    return out;
}

fn max_joltage(battery_bank: &Vec<u8>) -> u8 {
    let mut first:  u8 = 1;
    let mut second: u8 = 1;
    let mut out:    u8 = 0;

    for e in battery_bank {
        let e = *e;

        if second > first {
            first = second;
            second = 1;
        }
        
        if e > second {
            second = e;
        }

        out = first * 10 + second;

        if out == 99 {
            return 99;
        }
    }

    return out;
}

fn get_first_answer(battery_matrix: &Vec<Vec<u8>>) -> u64 {
    let mut out: u64 = 0;

    for bank in battery_matrix {
        out += max_joltage(bank) as u64;
    }

    return out;
}

// Parte 2
const N_ACTIVE_BATTERIES: usize = 12;

fn new_max_joltage(battery_bank: &Vec<u8>) -> u64 {
    let mut chosen: [u8; N_ACTIVE_BATTERIES] = [1; N_ACTIVE_BATTERIES];
    let mut out: u64 = 0;

    for b in battery_bank {
        let b = *b;

        for i in 0..N_ACTIVE_BATTERIES {
            
        }
    }

    return out;
}

fn main() {
    let batteries    = read_batteries(_INPUT_PATH);
    let first_answer = get_first_answer(&batteries);

    println!("First answer: {}", first_answer);
}