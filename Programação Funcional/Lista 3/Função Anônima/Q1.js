const exec = (f, valor1, valor2) => f(valor1, valor2)

const saida = exec((aresta1, aresta2) => aresta1 * aresta2, 5, 3)
console.log(saida)