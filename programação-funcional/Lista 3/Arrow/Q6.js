const quantosIguais = (valor1, valor2, valor3) => {
    if(valor1 === valor2 && valor2 === valor3) { return 3 } 
    if(valor1 !== valor2 && valor1 !== valor3 && valor2 !== valor3) { return 0 } 
    
    return 2
}

console.log(quantosIguais(1, 2, 1))