const exec = (f, valor) => f(valor)

const saida = exec(
    (nome) => {
        const nomes = nome.split(' ')

        return `${nomes[1]}, ${nomes[0]}`
    },
    "Davi Araújo"
)

console.log(saida)