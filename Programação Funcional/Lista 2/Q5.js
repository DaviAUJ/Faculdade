function calcularDistancia(ponto1, ponto2) {
    if(ponto1.X === ponto1.Y) {
        return Math.abs(ponto1.Y - ponto1.X)
    } else if(ponto2.X === ponto2.Y) {
        return Math.abs(ponto2.Y - ponto2.X)
    } else {
        return ((ponto2.X - ponto1.X) ** 2 + (ponto2.Y - ponto1.Y) ** 2 ) ** (1/2)
    }
}

const A = {
    X: -24,
    Y: -27
}
const B = {
    X: -3,
    Y: 1
}

console.log(`A distância entre os dois ponto é ${calcularDistancia(A, B)}`)