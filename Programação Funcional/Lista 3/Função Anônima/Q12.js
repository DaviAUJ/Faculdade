const exec = (f, valor1, valor2, valor3) => f(valor1, valor2, valor3)

const saida = exec(
    (a, b, c) => {
        const delta = b ** 2 - 4 * a * c
        
        if(delta > 0) {
            return [
                (-b + delta ** (1/2)) / (2 * a),
                (-b - delta ** (1/2)) / (2 * a)
            ]

        } else if(delta === 0) {
            return -b / (2 * a)

        } else {
            return "As raizes não são reais"
        }
    },
    -1,
    20,
    0
)

console.log(saida) 
