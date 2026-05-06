const { print } = require("../abbb.js")

Array.prototype.somaAninhado = function() {
    if(this.length === 0) { return "Lista Vazia" }
    
    const aux = ([x, ...xs]) => {
        if(typeof x === "object") { 
            if(xs.length === 0) { return aux(x) }
        
            return aux(xs) + aux(x)

        } else {
            if(xs.length === 0) { return x }

            return aux(xs) + x

        }
    }

    return aux(this)
}

const teste1 = [ 1, 2, 3 ] // Esperado 6
const teste2 = [ 1, 3, 2, 1, 4, 5, 6, 7] // Esperado 29
const teste3 = [ 1, [ 1, 2, 3 ], 3] // Esperado 10
const teste4 = [ [ 1, 2, 3 ], 1, 3 ] // Esperado 10
const teste5 = [ 1, 3, [ 1, 2, 3 ] ] // Esperado 10
const teste6 = [ [ 1, 2, 3, 4, 5 ], [ 1, 2, 3, 4, 5 ], [ 1, 2, 3, 4, 5 ], [ 1, 2, 3, 4, 5 ], [ 1, 2, 3, 4, 5 ] ] // Esperado 75
const teste7 = [ 5, [1, 5, [[1, 2, 3], 5, 1], 1, 2, [5, 1, [1, [2, [3, 5]]]], [5, 1, 2, 3]], 1, 2, 3, 4, [[[[[[[[[6]]]]]]]]], 1, [1, [3, [4]], 1, 2, 3] ]
// Esperado 85

print(teste1.somaAninhado())
print(teste2.somaAninhado())
print(teste3.somaAninhado())
print(teste4.somaAninhado())
print(teste5.somaAninhado())
print(teste6.somaAninhado())
print(teste7.somaAninhado())
