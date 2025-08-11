const exec = (f, valor1, valor2, valor3) => f(valor1, valor2, valor3)

const saida = exec(
    quantosIguais = (valor1, valor2, valor3) => {
        if(valor1 === valor2 && valor2 === valor3) { return 3 } 
        if(valor1 !== valor2 && valor1 !== valor3 && valor2 !== valor3) { return 0 }
    
        return 2
    },
    1,
    2,
    1
)

console.log(saida)