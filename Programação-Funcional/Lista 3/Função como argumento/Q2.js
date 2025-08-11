const exec = (f, valor1, valor2) => f(valor1, valor2)

const areaCirculo = (raio, pi=3.1415) => pi * raio ** 2

console.log(
    exec(areaCirculo, 5)
)