const { print } = require("../abbb.js")

const exp2 = (n) => {
    if(n === 0) { return 1 }

    return exp2(n - 1) * 2
}

print(exp2(20))
