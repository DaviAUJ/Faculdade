// Feito por Davi Araújo, Lucas Emanuel e Willard dos Santos

const adicionarLivro = (lista, titulo, autor, ano, genero) => lista.concat({ titulo: titulo, autor: autor, ano: ano, genero: genero })

function listarLivros(lista) {
    lista.map(
        (item, index) => {
            console.log(`${index} - ${item.titulo} \n${item.autor} \n${item.genero} \n${item.ano} \n`)
        }
    )
}

function buscarPorGenero(lista, genero) {
    const output = lista.filter(
        (item) => item.genero === genero
    )

    return output
}

function removerLivro(lista, titulo) {
    const temp = lista.filter(
        (item) => titulo !== item.titulo
    )

    return temp
}

function ordenarPorAno(lista) {
    const output = [...lista].sort(
        (a, b) => a.ano - b.ano
    )

    return output
}

function contagemPorGenero(lista, genero) {
    const temp = buscarPorGenero(lista, genero).reduce(
        (acc) => acc + 1, 0
    )

    return temp
}

function editarLivro(lista, index, detalhe, novoValor) {
    const output = lista.map(
        (item, indexItem) => {
            if(index === indexItem) { 
                if(detalhe === "titulo") { return { titulo: novoValor, autor: item.autor, ano: item.ano, genero: item.genero } }
                if(detalhe === "autor") { return { titulo: item.titulo, autor: novoValor, ano: item.ano, genero: item.genero } }
                if(detalhe === "ano") { return { titulo: item.titulo, autor: item.autor, ano: novoValor, genero: item.genero } }
                if(detalhe === "genero") { return { titulo: item.titulo, autor: item.autor, ano: item.ano, genero: novoValor } }
            }

            return item
        }
    )

    return output
} 

const livros = [
    { titulo: "Jogador Número 1", autor: "Ernest Cline", ano: 2011, genero: "Ficção Científica" },
    { titulo: "Os Miseráveis" , autor: "Victor Hugo" , ano: 1862 , genero: "Romance"},
    { titulo: "Percy Jackson O Ladrão de Raios", autor: "Rick Riordan", ano: 2005, genero: "Fantasia" }
]

// Função para adicionar livro
console.log("adicionarLivro():\n\n",
    adicionarLivro(livros, "As Aventuras na Netoland com Luccas Neto", "Luccas Neto", 2018, "Infantil")
)

console.log("\nlistarLivros: \n")
listarLivros(livros)