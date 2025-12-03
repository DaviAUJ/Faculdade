// Day 2: Gift Shop

use std::{fs::read_to_string, process::Output};

// Part 1
// Algoritmo ruim mas ainda roda rápido
#[derive(Debug)]
struct Range(u64, u64);

impl Range {
    fn new() -> Range {
        return Range(0, 0);
    }
}

const _INPUT_PATH: &str = "./src/bin/day_2/input";
const _TEST_PATH:  &str = "./src/bin/day_2/test";

fn read_file(name: &str) -> Vec<Range> {
    let mut output: Vec<Range> = Vec::new();
    output.reserve(1_000);

    let text = read_to_string(name).unwrap();

    for e in text.split(',') {
        let mut item = Range::new();
        let mut range_text = e.split('-');

        item.0 = range_text
            .next()
            .unwrap()
            .parse::<u64>()
            .unwrap();

        item.1 = range_text
            .next()
            .unwrap()
            .parse::<u64>()
            .unwrap();

        output.push(item);
    }

    return output;
}

fn count_digits(mut n: u64) -> u8 {
    let mut output: u8 = 0;

    while n != 0 {
        output += 1;
        n /= 10;
    }

    return output;
}

fn check_validity(n: u64) -> bool {
    let n_digits = count_digits(n);
    
    if n_digits % 2 == 1 {
        return true;
    }
    
    let n_digits = n_digits / 2;
    let shift = 10u64.pow(n_digits as u32);
    let high = n / shift;

    return (high * shift + high) != n;
}

fn sum_all_invalids(range_vec: &Vec<Range>) -> u64{
    let mut output: u64 = 0;

    for e in range_vec {
        for i in e.0 ..= e.1 {
            if !check_validity(i) {
                output += i;
            }
        } 
    }

    return output;
}

// Part 2
fn isolate_first_digits(n: u64, d: u8) -> u64 {
    let shift  = 10u64.pow(d as u32);
    let output = n / shift;
    let output = output * shift;
    let output = n - output;

    return output;
} 

//fn check_new_validity(n: u64) -> bool {
//    let n_digits = count_digits(n)
//}
//
//fn sum_all_new_invalids(range_vec: &Vec<Range>) -> u64 {
//    let output: u64 = 0;
//    
//
//}

fn main() {
    //let range_vec    = read_file(_INPUT_PATH);
    //let first_answer = sum_all_invalids(&range_vec);

    println!("First answer: {}", isolate_first_digits(12032, 4));
}