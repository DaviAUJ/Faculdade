const nomes0 = [ 'Ana', 'Bia', 'Marcela', 'Carlos', 'Maria', 'Paulo', 'Davi' ]
const nomes1 = [ 'Bia', 'João', 'Marcela' ,'Carlos' ,'Camila', 'Davi', 'Marcos' ]

const elementosRepetidos = (lista0) => (lista1) => {
    const listaTemp = lista0.filter(
        (item) => lista1.indexOf(item) !== -1
    )

    return listaTemp.length
}

console.log(
    elementosRepetidos(nomes0)(nomes1)
)
