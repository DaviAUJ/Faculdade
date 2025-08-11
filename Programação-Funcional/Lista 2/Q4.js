function definirTriangulo(lado1, lado2, lado3) {
    if(lado1 === lado2 && lado1 === lado3 && lado2 === lado3) {
        return "Equilátero"
    } else if(lado1 !== lado2 && lado1 !== lado3 && lado2 !== lado3) {
        return "Escaleno"
    } else {
        return "isósceles"
    }
}

const resultado = definirTriangulo(1, 1, 1)
console.log(resultado)