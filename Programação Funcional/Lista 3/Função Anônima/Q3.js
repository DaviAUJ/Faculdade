// Condição de existência de um triângulo se dá pela regra:
// a < b + c
// b < a + c
// c < a + b
const exec = (f, valor1, valor2, valor3) => f(valor1, valor2, valor3)

const saida = exec(
    (lado1, lado2, lado3) => {
        if(lado1 + lado2 > lado3 && lado1 + lado3 > lado2 && lado2 + lado3 > lado1) {
            return "É possível formar um triângulo"
        } else {
            return "Não é possível formar um triângulo"
        }
    },
    15,
    20, 
    30
)

console.log(saida)