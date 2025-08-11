const { composite, log, range, sum, equals, indef } = require('./utils.js')

const lista = [ 1, 2, 3, 4, 5, 6 ]

function divisaoInteira(dividendo, divisor) {
    return Math.floor(dividendo / divisor)
}

function multiplicarElementos(lista, vezes) {
    const temp = range(1, lista.length * vezes)

    const output = temp.map(
        (item, index) => lista[divisaoInteira(index, vezes)]
    )

    return output
}

log(
    multiplicarElementos(lista, 2)
)