function nomeBibliografico(nome) {
    const nomes = nome.split(' ')
    return `${nomes[1]}, ${nomes[0]}`
}

const nome = "Davi Araújo"

console.log(nomeBibliografico(nome))