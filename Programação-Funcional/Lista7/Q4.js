const { print } = require("../abbb.js")

Array.prototype.estaDentro = function(elemento) {
    if(this.length === 0) { return "Lista Vazia" }

    const aux = ([x, ...xs]) => {
        if(xs.length === 0) { return x === elemento }

        return x === elemento || aux(xs)
    }

    return aux(this)
}

String.prototype.vogais = function() {
    if(this.length === 0) { return "String Vazia" }
    
    const vogais = [ "á", "à", "â", "ã", "ê", "é", "í", "ó", "ô", "õ", "ú", "a", "e", "i", "o", "u" ]

    const aux = ([x, ...xs]) => {
        if(xs.length === 0) { 
            if(vogais.estaDentro(x)) { return 1 }
            else { return 0 }
        }

        if(vogais.estaDentro(x)) { return 1 + aux(xs) }
        else { return 0 + aux(xs) }
    }

    return aux(this.toLowerCase())
}

const teste1 = "um dois tres" // 4
const teste2 = "UM DOIS TRES" // 4
const teste3 = "UM DOIS TRÊS" // 4
const teste4 = "ÍÍÍÍÍÍÍÍÍÍííjgjgjgjgjgjgjgiíííà" // 17
const teste5 = "" // String Vazia
const teste6 = "falta bem poquin pra daqui a pouco" // 14
const teste7 = "falta bem poquin PARA DAQUI A pouco" // 15

print(teste1.vogais())
print(teste2.vogais())
print(teste3.vogais())
print(teste4.vogais())
print(teste5.vogais())
print(teste6.vogais())
print(teste7.vogais())