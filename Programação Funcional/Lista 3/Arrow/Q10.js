const nomeBibliografico = (nome) => {
    const nomes = nome.split(' ')

    return `${nomes[1]}, ${nomes[0]}`
}

console.log(nomeBibliografico("Davi Araújo"))