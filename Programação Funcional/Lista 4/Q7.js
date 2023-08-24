const { print } = require("../abbb.js")

const quociente = (dividendo, divisor) => {
    if(dividendo < divisor) { return 0 }
    
    return quociente(dividendo - divisor, divisor) + 1
}

print(quociente(5, 5))
