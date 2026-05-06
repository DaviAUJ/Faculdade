const { print, range, listSum } = require("../abbb.js")

const resto = (dividendo, divisor) => {
    if(dividendo < divisor) { return dividendo }
    
    return resto(dividendo - divisor, divisor)
}

const quociente = (dividendo, divisor) => {
    if(dividendo < divisor) { return 0 }
    
    return quociente(dividendo - divisor, divisor) + 1
}

// Retorna o próximo primo se não for um
const proxPrimo = (n) => {
    if(listSum(range(1, n).map((x) => resto(n, x) === 0 ? 1 : 0)) === 2) {
        return n
    }

    return proxPrimo(n + 1)
}

const mdc = (m, n, acc=2) => {
    const primodavez = proxPrimo(acc)

    if(m === 1 && n === 1) { return 1 }

    if(resto(m, primodavez) === 0 && resto(n, primodavez) === 0) {
        return mdc(quociente(m, primodavez), quociente(n, primodavez)) * primodavez
    }

    if(resto(m, primodavez) === 0) {
        return mdc(quociente(m, primodavez), n)
    }

    if(resto(n, primodavez) === 0) {
        return mdc(m, quociente(n, primodavez))
    }

    return mdc(m, n, primodavez + 1)
}

print(mdc(20, 24))

