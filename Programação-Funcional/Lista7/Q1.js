const { print } = require("../abbb.js")

Array.prototype.busca = function(item) {
    const aux = (item, [x, ...xs]) => {
        if(x === item) { return 0 }
        if(xs.length === 0 ) { return this.length * -1 }

        return aux(item, xs) + 1
    }

    if(this.length === 0) { return "Lista Vazia" }

    return aux(item, this)
}

const teste = [ "b", "l", "u", "L", "r", "q", "a", "qq" ]
const teste1 = [ ]

print(
    teste1.busca("1")
)