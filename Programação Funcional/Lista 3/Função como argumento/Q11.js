const exec = (f, valor1, valor2, valor3) => f(valor1, valor2, valor3)

const maioresQueMedia = (valor1, valor2, valor3) => {
    const media = (valor1 + valor2 + valor3) / 3

    return (valor1 > media ? 1 : 0) + (valor2 > media ? 1 : 0) + (valor3 > media ? 1 : 0)
}

console.log(
    exec(maioresQueMedia, 10, 11, 10)
)
