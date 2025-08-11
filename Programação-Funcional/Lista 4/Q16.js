const { print, divisaoInteira } = require("../abbb.js")

const conversorBase = (base) => (num) => {
    const algarismos = [ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" ]

    if(divisaoInteira(num, base) === 0) { return `${algarismos[num % base]}` }

    return conversorBase(base)(divisaoInteira(num, base)) + `${algarismos[num % base]}`
}

module.exports = { conversorBase }