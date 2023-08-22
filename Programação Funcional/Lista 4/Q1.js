const { print } = require('../abbb.js')

const prog = (n) => {
    if(n === 1) { return 3 }
    
    return prog(n - 1) * 2
}

print(prog(10))
