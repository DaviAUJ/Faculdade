// Segunda tentaviva

function menorValor(lista){
    if(lista[0] <= lista[1] && lista[0] <= lista[2]) {
        return lista[0]

    } else if(lista[1] <= lista[0] && lista[1] <= lista[2]) {
        return lista[1]

    } else {
        return lista [2]

    }
}

const lista = [ -5, -5, -3 ]

console.log(menorValor(lista))