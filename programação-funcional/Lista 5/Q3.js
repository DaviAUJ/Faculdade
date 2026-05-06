const valores = [ 3, 5, -1, 4, 0 ]

const tamanho = (lista) => lista.reduce((acc) => acc + 1, 0)

console.log(
    tamanho(valores)
)