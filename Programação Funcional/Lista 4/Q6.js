const { print } = require("../abbb.js")

const resto = (dividendo, divisor) => {
    if(dividendo < divisor) { return dividendo }

    return resto(dividendo - divisor, divisor)
}

print(resto(36, 7))