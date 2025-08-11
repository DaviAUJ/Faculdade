const exec = (f, valor) => f(valor)

const sqrt = (n) => n ** 2
const quartapotencia = (n) => sqrt(sqrt(n))

console.log(
    exec(quartapotencia, 5)
)