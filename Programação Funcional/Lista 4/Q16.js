const { print, divisaoInteira } = require("../abbb.js")

const conversorBaseMenorQue16 = (base, num) => {
    const algarismos = [ "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" ]

    if(divisaoInteira(num, base) === 0) { return `${algarismos[num % base]}` }

    return conversorBaseMenorQue16(base, divisaoInteira(num, base)) + `${algarismos[num % base]}`
}
print(conversorBaseMenorQue16(2, 5763))