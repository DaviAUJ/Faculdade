Array.prototype.lengthPotente = function() {
    if(this.length === 0) { return 0 }
    
    const aux = ([x, ...xs], acc=0) => {
        if(xs.length === 0) {
            if(typeof x === "object") { return aux(x, acc) }
            return acc + 1
        }

        if(typeof x === "object") { return aux(xs, acc) + aux(x, 0) }
        return aux(xs, acc + 1)
    }

    return aux(this)
}

const teste1 = [ 1, 2, 3 ] 
const teste2 = [ 1, 3, 2, 1, 4, 5, 6, 7] 
const teste3 = [ 1, [ 1, 2, 3 ], 3]
const teste4 = [ [ 1, 2, 3 ], 1, 3 ]
const teste5 = [ 1, 3, [ 1, 2, 3 ] ]
const teste6 = [ [ 1, 2, 3, 4, 5 ], [ 1, 2, 3, 4, 5 ], [ 1, 2, 3, 4, 5 ], [ 1, 2, 3, 4, 5 ], [ 1, 2, 3, 4, 5 ] ]
const teste7 = [ 5, [1, 5, [[1, 2, 3], 5, 1], 1, 2, [5, 1, [1, [2, [3, 5]]]], [5, 1, 2, 3]], 1, 2, 3, 4, [[[[[[[[[6]]]]]]]]], 1, [1, [3, [4]], 1, 2, 3] ]

console.log(teste1.lengthPotente())
console.log(teste2.lengthPotente())
console.log(teste3.lengthPotente())
console.log(teste4.lengthPotente())
console.log(teste5.lengthPotente())
console.log(teste6.lengthPotente())
console.log(teste7.lengthPotente())
