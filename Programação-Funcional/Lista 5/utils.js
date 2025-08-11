/**
 * composite()
 *
 * Função para compor um pipeline de funções.
 */
const composite = (...fns) => 
      (value) => fns.reduce((acc,fn) => fn(acc), value)

/**
 * log()
 *
 * Simplifica a função de exibição de resultados.
 */
const log = (str) => console.log(str)

/**
 * range()
 *
 * Retorna um conjunto de números entre um número inicial e um número final incrementado
 * sequencialmente por um número fixo (passo), começando com o número inicial ou
 * o número final, dependendo de qual é menor.
 * Exemplo: range(3,9) ---> [3,4,5,6,7,8,9]
 * Exemplo: range(8,0,2) ---> [8,6,4,2,0]
 * Exemplo: range(1,5,0.5) ---> [1,1.5,2,2.5,3,3.5,4,4.5,5]
 */
const range = (start, end, step = 1) => {
    // Testa se os 3 primeiros argumentos são números finitos,
    // usando Array.every() e Number.isFinite()
    const allNumbers = [start, end, step].every(Number.isFinite)
    // Lança um erro se algum dos 3 primeiros argumentos não for um número finito.
    if (!allNumbers) {
      throw new TypeError('range() espera apenas números finitos como argumentos.')
    }
    // Assegura que o passo é sempre um número positivo.
    if (step <= 0) {
      throw new Error('passo deve ser um número maior que zero.')
    }
    // Quando o número inicial é maior do que o número final,
    // modifica o passo para decrescer em vez de incrementar.
    if (start > end) {
      step = -step
    }
    // Determina o comprimento do conjunto a ser retornado.
    // O comprimento é incrementado em 1 após Math.floor().
    // Isto assegura que o número final é listado se estiver dentro do intervalo.
    const length = Math.floor(Math.abs((end - start) / step)) + 1
    // Preenche um novo conjunto com os números do intervalo
    // usando o Array.from() com uma função de mapeamento.
    // Finalmente, retorna o novo array.
    return Array.from(Array(length), (x, index) => start + index * step)
}

/**
 * sum()
 *
 * Função que retorna os elementos de uma lista.
 */
const sum = (list) => list.reduce((acc,x)=>acc+x,0)

/**
 * equals()
 *
 * Função que compara se duas listas são iguais.
 * Elas precisam ter o mesmo comprimento e, obviamente,
 * os mesmos elementos.
 */
const equals = (list1, list2) =>
  list1.length === list2.length &&
  list1.every((value, i) => value === list2[i]);

/**
 * indef()
 *
 * Função que testa se um elemento é indefinido.
 * Útil para operações de recursividade em listas.
 */ 
const indef = x => typeof x == 'undefined'

module.exports = {composite, log, range, sum, equals, indef}