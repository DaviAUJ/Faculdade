Array.prototype.meuFilter = function(funcao) {
    if(this.length === 0) { return [ ] }

    const aux = ([x, ...xs]) => {
        if(xs.length === 0) { return funcao(x) ? [ x ] : [ ] }

        return funcao(x) ? [ x, ...aux(xs) ] : [ ...aux(xs) ]
    }

    return aux(this)
}

const ehPar = (x) => x % 2 === 0

const teste1 = []
const teste2 = [ 1 ]
const teste3 = [ 2 ]
const teste4 = [ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ]

console.log(
    teste1.meuFilter(ehPar)
)

console.log(
    teste2.meuFilter(ehPar)
)

console.log(
    teste3.meuFilter(ehPar)
)

console.log(
    teste4.meuFilter(ehPar)
)