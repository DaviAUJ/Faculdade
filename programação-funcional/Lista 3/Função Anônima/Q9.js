const exec = (f, valor1, valor2) => f(valor1, valor2)

const saida = exec(
    (valor1, valor2) => {
        if(valor1 == valor2) { return false } 
        
        return true
    },
    true,
    false
)

console.log(saida)
