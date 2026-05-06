const { conversorBase } = require("./Q16.js")
const { unirLista, print, inverte } = require("../abbb.js")

const conversorBase2 = conversorBase(2)

const binarioParaBase10 = (binario, exp=0) => {
    if(exp === binario.length - 1) { return parseInt(inverte(binario)[exp]) * 2 ** exp }

    return binarioParaBase10(binario, exp + 1) + parseInt(inverte(binario)[exp]) * 2 ** exp
}

const bitShift = (num, vezes) => {
    if(vezes === 0) { return num }

    if(typeof num === "number") {
        const output = [...conversorBase2(num)].map(
            (x, index, array) => {
                if(index === 0) { return array[array.length - 1] }
    
                return array[index - 1]
            }
        )

        return bitShift(unirLista(output), vezes - 1)

    } else {
        const output = [...num].map(
            (x, index, array) => {
                if(index === 0) { return array[array.length - 1] }
    
                return array[index - 1]
            }
        )

        return bitShift(unirLista(output), vezes - 1)
    }
}

print(bitShift(81, 3))