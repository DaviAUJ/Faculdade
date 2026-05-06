const lado1 = 16
const lado2 = 20
const lado3 = 30

// Condição de existência de um triângulo se dá pela regra:
// a < b + c
// b < a + c
// c < a + b
if(lado1 + lado2 > lado3 && lado1 + lado3 > lado2 && lado2 + lado3 > lado1) {
    console.log("É possível formar um triângulo")
} else {
    console.log("Não é possível formar um triângulo")
}