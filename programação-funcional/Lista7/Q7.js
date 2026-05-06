Array.prototype.quickSort = function() {
    if(this.length === 0) { return this }

    const aux = ([x, ...xs]) => {
        const menores = xs.filter( (i) => i <= x ) //Se retirar o = do <= ele ordena e remove os elementos repetidos
        const maiores = xs.filter( (i) => i > x )

        return [...menores.quickSort(), x, ...maiores.quickSort()]
    }

    return aux(this)
}

const teste1 = [ 1, 2, 3, 4, 5 ]
const teste2 = [ 2, 3, 6, 1, 7, 10, 4]
const teste3 = [ 1, 2, 2, 3, 4, 4, 5]
const teste4 = [ 4, 2, 7, 1, 2, 2, 3, 5, 1, 5]

console.log(teste1.quickSort())
console.log(teste2.quickSort())
console.log(teste3.quickSort())
console.log(teste4.quickSort())