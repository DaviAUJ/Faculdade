const exec = (f, valor1, valor2) => f(valor1, valor2)

const areaRetangulo = (aresta1, aresta2) => aresta1 * aresta2

console.log(
    exec(areaRetangulo, 5, 3)
)