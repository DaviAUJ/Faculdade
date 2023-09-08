const { print } = require("../abbb.js")

Array.prototype.maior = function() {
    if(this.length === 0) { return "Lista Vazia" }

    const aux = ([x, ...xs], acc=x) => {   
        if(xs.length === 0) { 
            if(x > acc) { return x }
            else { return acc }
        }

        if(x > acc) { return aux(xs, x) }
        else { return aux(xs, acc) }
    }

    return aux(this)
}

const teste = [ 837, 38, 97, 322, 452, 745, 352, 825, 41, 460, 429, 499, 358 ]
const teste1 = [ ]

print(
    teste1.maior()
)
