function maioresQueMedia(a, b, c) {
    const inputs = [ a, b, c ]
    const media = (a + b + c) / 3

    const resultado = inputs.filter(x => x > media)
    return resultado.length
}

const output = maioresQueMedia(10, 12, 12)
console.log(output)
