const nomeBibliografico = (nome) => (sobrenome) => `${sobrenome}, ${nome}`

const comecacomDavi = nomeBibliografico("Davi")

console.log(
    comecacomDavi("Araújo")
)