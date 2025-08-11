function quantosIguais(valor1, valor2, valor3) {
    if(valor1 === valor2 && valor1 === valor3 && valor2 === valor3) {
        return 3
    } else if(valor1 !== valor2 && valor1 !== valor3 && valor2 !== valor3) {
        return 0
    } else {
        return 2
    }
}

const resultado = quantosIguais(1, 2, 3)
console.log(resultado)