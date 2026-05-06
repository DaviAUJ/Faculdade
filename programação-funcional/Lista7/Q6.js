Array.prototype.somaSequencial = function() {
    if(this.length === 0) { return "Lista Vazia" }

    const aux = ([x, ...xs], fator=0) => {
        if(xs.length === 0) { return [x + fator] }

        return [x + fator, ...aux(xs, x + fator)]
    }

    return aux(this)
}

const teste1 = [ 7, 3, 19, 5, 15, 10 ]
const teste2 = [1,2,5,5,13,8,3,1,1,0]

console.log(teste2.somaSequencial())
