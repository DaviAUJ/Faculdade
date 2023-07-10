const exec = (f, valor1, valor2) => f(valor1, valor2)

const ouExclusivo = (valor1, valor2) => {
    if(valor1 == valor2) { return false } 
    
    return true
}

console.log(
    exec(ouExclusivo, true, true)
)