const exec = (f, valor) => f(valor)

const saida = exec(
    (n) => exec(
        (n) => n ** 2,
        exec(
            (n) => n ** 2,
            n
        )
    ),
    5
)

console.log(saida)
