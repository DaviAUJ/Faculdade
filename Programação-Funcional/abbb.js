const print = (str) => console.log(str)

const listSum = (list) => list.reduce( (acc, x) => acc + x )

function divisaoInteira(dividendo, divisor) {
  return Math.floor(dividendo / divisor)
}

const range = (start, end, step = 1) => {
  const allNumbers = [start, end, step].every(Number.isFinite)

    if (!allNumbers) {
      throw new TypeError('range() espera apenas números finitos como argumentos.')
    }

    if (step <= 0) {
      throw new Error('passo deve ser um número maior que zero.')
    }

    if (start > end) {
      step = -step
    }

    const length = Math.floor(Math.abs((end - start) / step)) + 1

    return Array.from(Array(length), (x, index) => start + index * step)
}

const inverte = (string, acc=0) => {
  if(acc === string.length) { return '' }

  return inverte(string, acc + 1) + string[acc]
}

const unirLista = (lista, acc=0) => {
  if(acc === lista.length - 1) { return lista[lista.length - 1] }

  return lista[acc] + unirLista(lista, acc + 1)
}

const isUndef = (x) => typeof x === "undefined"

module.exports = { print, listSum, divisaoInteira, range, inverte, unirLista, isUndef }