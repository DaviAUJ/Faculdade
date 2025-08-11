function calcularDistancia(ponto1, ponto2) {
    if(ponto1.X === ponto2.X) {
        return Math.abs(ponto1.Y - ponto2.Y)
    } else if(ponto1.Y === ponto2.Y) {
        return Math.abs(ponto1.X - ponto2.X)
    } else {
        return ((ponto2.X - ponto1.X) ** 2 + (ponto2.Y - ponto1.Y) ** 2 ) ** (1/2)
    }
}

const A = {
    X: 1,
    Y: 5
}
const B = {
    X: -10,
    Y: 5
}

console.log(`A distância entre os dois ponto é ${calcularDistancia(A, B)}`)