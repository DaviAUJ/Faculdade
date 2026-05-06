const exec = (f, valor1, valor2) => f(valor1, valor2)

const velocidade = (tempo, espaço) => (espaço - 500) / tempo

console.log(
    exec(velocidade, 5, 1000)
)
