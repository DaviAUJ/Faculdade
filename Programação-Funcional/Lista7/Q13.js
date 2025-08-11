const digitosoma = (numero) => {
    const numStr = `${numero}`

    const aux = ([x, ...xs]) => {
        if(xs.length === 0) { return parseInt(x) }

        return parseInt(x) + aux(xs)
    }

    if(numStr.length === 1) { return parseInt(numStr) }
    return digitosoma(aux(numStr))
}

const teste1 = 123
const teste2 = 999888777
const teste3 = 999999999998

console.log(digitosoma(teste1))
console.log(digitosoma(teste2))
console.log(digitosoma(teste3))