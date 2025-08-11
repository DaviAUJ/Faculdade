const carrinho = [
    { nome: 'Caneta', qtde: 10, preco: 7.99, fragil: true },
    { nome: 'Impressora', qtde: 1, preco: 649.50, fragil: true },
    { nome: 'Caderno', qtde: 4, preco: 27.10, fragil: false },
    { nome: 'Lapis', qtde: 3, preco: 5.82, fragil: false },
    { nome: 'Tesoura', qtde: 1, preco: 19.20, fragil: true },
]

// Letra A
const aplicarCambio = (moeda) => (carrinho) => {
    const tabelaConversao = {
        dolar: 4.81,
        kwanza: 0.0058,
        euro: 5.26
    }

    const output = carrinho.map((item) => {
        return {
            nome: item.nome,
            qtde: item.qtde,
            preco: parseFloat((item.preco / tabelaConversao[moeda]).toFixed(2)),
            fragil: item.fragil
        }
    })

    return output
}

// Letra B
const precoFinal = (carrinho) => {
    const subTotalItem = (acc, item) => acc + item.qtde * item.preco

    return parseFloat(carrinho.reduce(subTotalItem, 0).toFixed(2))
}

// Letra C
const desconto = (porcentagem) => (valor) => valor * (1 - porcentagem / 100)

// Letra D
const precoFinalTipo = (fragilidade) => (carrinho) => {
    const carrinhoTemp = carrinho.filter(
        (item) => item.fragil === fragilidade
    )

    return precoFinal(carrinhoTemp)
}

const precoFinalFragil = precoFinalTipo(true)

// Letra E
const precoFinalLetra = (letra) => (carrinho) => {
    const carrinhoTemp = carrinho.filter(
        (item) => item.nome[0].toUpperCase() === letra.toUpperCase()
    )

    return precoFinal(carrinhoTemp)
}

// Letra F
// Perguntar ao prof