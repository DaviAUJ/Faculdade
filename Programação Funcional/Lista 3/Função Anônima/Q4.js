const exec = (f, valor1, valor2, valor3) => f(valor1, valor2, valor3)

const saida = exec(
    (lado1, lado2, lado3) => {
        if(lado1 === lado2 && lado2 === lado3) {
            return "Equilátero"
        } else if(lado1 !== lado2 && lado1 !== lado3 && lado2 !== lado3) {
            return "Escaleno"
        } else {
            return "isósceles"
        }
    },
    1,
    2,
    3
)
    
console.log(saida)