const { composite, log, range, sum, equals, indef } = require('./utils.js')

function algarismos(num, qtde) {
    const numString = num.toString()

    if(numString.length < qtde) { return "Erro" }

    return numString.slice(0, qtde)
}

log(
    algarismos(29345872837, 5)
)