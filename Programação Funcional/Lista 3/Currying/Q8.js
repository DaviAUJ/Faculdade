const exponenciacao = (expoente) => (base) => base ** expoente

const quadrado = exponenciacao(2)
const quartaPotencia = (numero) => quadrado(quadrado(numero))

console.log(quartaPotencia(3))
