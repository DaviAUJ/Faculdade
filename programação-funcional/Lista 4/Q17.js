const collatz = (num) => {
    if(num === 1) { return 0 }

    if(num % 2 === 0) { return collatz(num / 2) + 1 } 
    return collatz(3 * num + 1) + 1
}

const repetir = (acc=2) => {
    if(collatz(acc) >= 200) { console.log(`${acc} - ${collatz(acc)}`) }

    return repetir(acc + 1)
}

repetir()