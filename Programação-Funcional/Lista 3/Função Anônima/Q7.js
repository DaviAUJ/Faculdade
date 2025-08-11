const exec = (f, lista) => f(lista)

const saida = exec(
    (lista) => {
        if(lista[0] <= lista[1] && lista[0] <= lista[2]) { return lista[0] } 
        if(lista[1] <= lista[0] && lista[1] <= lista[2]) { return lista[1] } 
        
        return lista[2]
    },
    [ -5, -10, -3 ]
)

console.log(saida)