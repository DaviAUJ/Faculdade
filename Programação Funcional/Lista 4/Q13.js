const somaQuadrados = (n) => {
    if(n === 1) { return 1 }

    return somaQuadrados(n - 1) + n ** 2
}

console.log(somaQuadrados(8))