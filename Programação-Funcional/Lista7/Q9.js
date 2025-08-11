Array.prototype.elimina = function(termo) {
    if(this.length === 0) { return [] }

    const aux = ([x, ...xs]) => {
        if(xs.length === 0) { 
            if(x === termo) { return []}
            else { return [x] }
         }

        if(x === termo) { return [...aux(xs)]}
        else { return [x, ...aux(xs)]}
    }

    return aux(this)
}

const teste1 = [ -4, 0, 3, 7, 11 ] 
const teste2 = [ 0, 1, 1, 2, 3, 4, 1, 0] 
const teste3 = [0, 0]
const teste4 = []

console.log(teste1.elimina(7))
console.log(teste2.elimina(1))
console.log(teste3.elimina(0))
console.log(teste4.elimina(1))