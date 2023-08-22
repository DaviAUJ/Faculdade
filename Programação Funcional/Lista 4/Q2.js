const { print } = require("../abbb.js")

const fibonacci = (n) => {
    if(n === 2) { return 1 }
    if(n === 1) { return 0 }
    
    return fibonacci(n - 1) + fibonacci(n - 2)
}

print(fibonacci(22))