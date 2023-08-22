const { print } = require("../abbb.js")

const fatorial = (n) => {
    if(n === 2) { return 2 }

    return fatorial(n - 1) * n
}

print(fatorial(10))