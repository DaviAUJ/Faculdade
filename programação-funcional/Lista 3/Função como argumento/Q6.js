const exec = (f, valor1, valor2, valor3) => f(valor1, valor2, valor3)

const quantosIguais = (valor1, valor2, valor3) => {
    if(valor1 === valor2 && valor2 === valor3) { return 3 } 
    if(valor1 !== valor2 && valor1 !== valor3 && valor2 !== valor3) { return 0 } 
    
    return 2
}

console.log(
    exec(quantosIguais, 20, 15, 12)
)