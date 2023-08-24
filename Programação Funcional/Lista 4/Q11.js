const multiSomaGeral = (m) => (n) => {
    if(m === 1) { return n }
    
    return multiSomaGeral(m - 1)(n) + m * n
}

const multiSoma = multiSomaGeral(10)

console.log(multiSoma(10))