Array.prototype.meuReduce = function(funcao, acc=0) {
    if(this.length === 0) { return [ ] }

    const aux = ([x, ...xs], accAux=acc) => {
        if(xs.length === 0) { return accAux + funcao(x) }

        return aux(xs, accAux + funcao(x))
    }

    return aux(this)
}

const quad = (x) => x ** 2

const teste1 = []
const teste2 = [ 1 ]
const teste3 = [ 1, 2, 3, 4 ]
const teste4 = [ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ]

console.log(
    teste1.meuReduce(quad)
)

console.log(
    teste2.meuReduce(quad)
)

console.log(
    teste3.meuReduce(quad)
)

console.log(
    teste4.meuReduce(quad)
)