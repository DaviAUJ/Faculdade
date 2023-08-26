const { conversorBase } = require("./Q16.js")
const { unirLista, print, inverte } = require("../abbb.js")

const conversorBase2 = conversorBase(2)

const binarioParaBase10 = (binario, exp=0) => {
    if(exp === binario.length - 1) { return parseInt(inverte(binario)[exp]) * 2 ** exp }

    return binarioParaBase10(binario, exp + 1) + parseInt(inverte(binario)[exp]) * 2 ** exp
}

const bitShiftDireita = (num, vezes) => {
    if(vezes === 0) { return binarioParaBase10(unirLista(num)) }

    if(typeof num === "number") {
        const output = [...conversorBase2(num)].map(
            (x, index, array) => {
                if(index === 0 && x !== 0) { return "0" }
    
                return array[index - 1]
            }
        )

        return bitShiftDireita(output, vezes - 1)

    } else {
        const output = num.map(
            (x, index, array) => {
                if(index === 0 && x !== 0) { return "0" }
    
                return array[index - 1]
            }
        )

        return bitShiftDireita(output, vezes - 1)
    }
}

print(bitShiftDireita(4567, 3))
