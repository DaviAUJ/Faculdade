const nums = [ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ]

const nnseiquenomedar = (lista) => {
    const quadradodasoma = lista.reduce((acc, item) => acc + item, 0) ** 2
    const somadosquadrados = lista.reduce((acc, item) => acc + item ** 2, 0)

    return quadradodasoma - somadosquadrados
}

console.log(
    nnseiquenomedar(nums)
)
