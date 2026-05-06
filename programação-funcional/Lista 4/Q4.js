const { print } = require("../abbb.js")

const fatorial = (n) => {
    if(n === 0) { return 1 }

    return fatorial(n - 1) * n
}

print(fatorial(5))