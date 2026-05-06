const { print } = require("../abbb.js")

Array.prototype.estaDentro = function(elemento) {
    if(this.length === 0) { return "Lista Vazia" }

    const aux = ([x, ...xs]) => {
        if(xs.length === 0) { return x === elemento }

        return x === elemento || aux(xs)
    }

    return aux(this)
}

Array.prototype.apenasEstes = function(...itens) {
    if(this.length === 0) { return false }

    const aux = ([x, ...xs], lista) => {
        if(xs.length === 0) { return lista.estaDentro(x) }
        
        return lista.estaDentro(x) && aux(xs, lista)
    }

    return aux(this, itens)
}

String.prototype.eliminaIntExc = function() {
    if(this.length === 0) { return "String Vazia" }

    const aux = ([x, y, ...xs]) => {
        if(xs.length === 0) { 
            if((x === '?' && y === '?') || (x === '!' && y === '!')) { return x }
            else { return x + y }
        }

        if([x, y, ...xs].apenasEstes('!', '?')) {
            if(x === y) { return aux([x, ...xs]) }
        }

        return x + aux([y, ...xs])
    }

    return aux(this)
}

const teste01 = "oiiiiiiiiiiiiiii"
const teste02 = "oiiiiiiiiiiiiiii!"
const teste03 = "oiiiiiiiiiiiiiii!!!!!!!!!!!!!!!!"
const teste04 = "oiiiiiiiiiiiiiii??????????????????"
const teste05 = "oiiiiiiiiiii?????!!!!!!!!!????????!!!!!!"
const teste06 = "????????!!!!!!opa?!?!?!??!!???!!!????!!!!" 
const teste07 = "????????"
const teste08 = "!!???!!!?!????!!"

print(teste01.eliminaIntExc())
print(teste02.eliminaIntExc())
print(teste03.eliminaIntExc())
print(teste04.eliminaIntExc())
print(teste05.eliminaIntExc())
print(teste06.eliminaIntExc())
print(teste07.eliminaIntExc())
print(teste08.eliminaIntExc())
