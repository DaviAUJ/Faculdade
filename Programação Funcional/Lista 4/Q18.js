const { inverte } = require("../abbb.js")

const unirLista = (lista, acc=0) => {
    if(acc === lista.length - 1) { return lista[lista.length - 1] }

    return lista[acc] + unirLista(lista, acc + 1)
}

const filtroString = (string) => {
    const output = [...string].filter(
        function suporte(item, index, array, acc=0) {
            const blacklist = [ "á", "à", "â", "ã", "ê", "é", "í", "ó", "ô", "õ", "ú", "-", ".", ",", "!", "?", ";", ":", " " ]

            if(acc === blacklist.length) { return true }
            if(item === blacklist[acc]) { return false}

            return suporte(item, index, array, acc + 1)
        }
    )

    return unirLista(output).toLowerCase()
}

const EPalindromo = (string) => filtroString(string) === inverte(filtroString(string))

console.log(
    EPalindromo('Socorram-me, subi no ônibus em marrocos!')
)