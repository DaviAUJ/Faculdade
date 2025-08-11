const exec = (f, valor1, valor2, valor3) => f(valor1, valor2, valor3)

// Condição de existência de um triângulo se dá pela regra:
// a < b + c
// b < a + c
// c < a + b
const verificarExistenciaTriangulo = (lado1, lado2, lado3) => {
    if(lado1 + lado2 > lado3 && lado1 + lado3 > lado2 && lado2 + lado3 > lado1) {
        return "É possível formar um triângulo"
    } else {
        return "Não é possível formar um triângulo"
    }
}

console.log(
    exec(verificarExistenciaTriangulo, 15, 20, 30)
)