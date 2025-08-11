Array.prototype.quickSort = function() {
    if(this.length === 0) { return this }

    const aux = ([x, ...xs]) => {
        const menores = xs.filter( (i) => i <= x ) 
        const maiores = xs.filter( (i) => i > x )

        return [...menores.quickSort(), x, ...maiores.quickSort()]
    }

    return aux(this)
}

Array.prototype.buscaBin = function(valor) {
    const ordenada = this.quickSort()

    const aux = (lista, pos=Math.floor(lista.length / 2)) => {
        if(lista.length === 0) { return -1 }

        const meio = Math.floor(lista.length / 2)

        if(lista[meio] === valor) { return pos }
        if(lista[meio] < valor) { 
            const listaNova = lista.slice(meio + 1, lista.length)
            console.log(listaNova)

            return aux(listaNova, pos + Math.floor(listaNova.length / 2) + 1)
        }
        if(lista[meio] > valor) { 
            const listaNova = lista.slice(0, meio)
            console.log(listaNova)

            return aux(listaNova, pos - Math.ceil(listaNova.length / 2))
        }
    }

    return aux(ordenada)
}

const teste1 = [668, 547, -981, 695, -873, 856, -727, -687, 723, -339, -686, 334, -772, -493, -359, 391, 151, -724, -469, -265, -306, 567, -13, -403, 606, -188, 314, -194, 333, -139, -803, 803, -153, -550, -346, -658, -682, -792, -637, 70, -279, 255, -49, 215, 324, -416, -517, 902, -656, 783, -731, 915, -866, 286, 444, 290, 116, 490, -138, -54, 938, -679, 979, -397, 851, -816, 720, 354, 370, 245, 730, -55, 93, 613, -715, 621, 561, 542, 279, 926, -252, -841, -920, -246, 449, -795, -154, 800, 684, 724, -372, -58, -23, -398, 989, -192, -576, 995, -872]

console.log(teste1.buscaBin(-54))

console.log(teste1.quickSort())