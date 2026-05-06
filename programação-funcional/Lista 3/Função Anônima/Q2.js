const exec = (f, valor1, valor2) => f(valor1, valor2)

saida = exec((raio, pi=3.1415) => pi * raio ** 2, 7)
console.log(saida)