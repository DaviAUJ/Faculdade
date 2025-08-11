const exec = (f, valor1, valor2) => f(valor1, valor2)

const saida = exec(
    (tempo, espaço) => (espaço - 500) / tempo,
    5,
    1000
)

console.log(saida)
