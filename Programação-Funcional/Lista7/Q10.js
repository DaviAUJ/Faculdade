Array.prototype.estaDentro = function(elemento) {
    if(this.length === 0) { return false }

    const aux = ([x, ...xs]) => {
        if(xs.length === 0) { return x === elemento }

        return x === elemento || aux(xs)
    }

    return aux(this)
}

Array.prototype.unicos = function() {
    if(this.length === 0) { return [] }

    const aux = ([x, ...xs], familiares=[]) => {
        if(xs.length === 0) {
            if(familiares.estaDentro(x)) { return [] }
            else { return [x]}
        }

        if(xs.estaDentro(x) || familiares.estaDentro(x)) { return [...aux(xs, [x, ...familiares])]}
        else { return [x, ...aux(xs, familiares)] }
    }

    return aux(this)
}

const teste1 = [ 4, 2, 1, 3, 2, 3 ]
const teste2 = [ 1, 4, 4, 2, 1, 3, 2, 3 ]
const teste3 = [ ]
const teste4 = [ 4, 4, 4, 4, 1, 1, 1, 1 ]
const teste5 = [ 1, 2, 3, 4, 5, 6, 7 ]

console.log(teste1.unicos())
console.log(teste2.unicos())
console.log(teste3.unicos())
console.log(teste4.unicos())
console.log(teste5.unicos())
