const exec = (f, valor) => f(valor)

const saida = exec(
    (num) => {
        const nomes = [
            "Um",
            "Dois",
            "Três",
            "Quatro",
            "Cinco",
            "Seis",
            "Sete",
            "Oito",
            "Nove",
            "Zero"
        ]
    
        // Verificação se o input é válido
        if(num > 9 || num < 0) { return "Error" }
        
        return nomes[num - 1]
    },
    9
)

console.log(saida)