const { composite, log, range, sum, equals, indef } = require('./utils.js')

const soma = (listaNum) => listaNum.reduce((acc, x) => acc + x)

function primos(num) {
    const output = range(2, num).filter(
        (item) => {
                const resultado = range(1, Math.floor(item / 2)).map(
                    (x) => item % x !== 0 ? 0 : 1
            )

            return soma(resultado) === 1
        }
    )

    return output
}

log(
    primos(1000)
)
