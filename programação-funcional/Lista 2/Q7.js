function comparar(numeros) {
    if (numeros[0] > numeros[1]) {
        if(numeros[1] > numeros[2]) {
            return numeros[2]

        } else if (numeros[1] < numeros[2]) {
            return numeros[1]

        } else {
            return numeros[1]

        }

    } else if(numeros[0] < numeros[1]) {
        if(numeros[0] < numeros[2]) {
            return numeros[0]

        } else if(numeros[0] > numeros[2]) {
            return numeros[2]

        } else {
            return numeros[0]
        }

    } else {
        return numeros[0]

    }
}
// Lista com 3 números
const lista = [ -5, 10, 41 ]
const menor = comparar(lista)
console.log(menor)