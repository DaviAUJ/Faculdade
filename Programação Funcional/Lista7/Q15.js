Array.prototype.meuMap = function(funcao) {
    if(this.length === 0) { return [] }

    const aux = ([x, ...xs]) => {
        if(xs.length === 0) { return [ funcao(x) ] }

        return [ funcao(x), ...aux(xs) ]
    }

    return aux(this)
}

const dobrar = (x) => x * 2

const teste1 = []
const teste2 = [ 1 ]
const teste3 = [ 1, 2, 3, 4, 5, 6, 7, 8 ]

console.log(teste1.meuMap(dobrar))
console.log(teste2.meuMap(dobrar))
console.log(teste3.meuMap(dobrar))