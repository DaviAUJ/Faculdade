const pontuacao = (...jogos) => {
    if(jogos.length === 0) { return 0 }

    const aux = ([x, ...xs], acc=0) => {
        if(x[0] === x[1]) { return 0 }
        if(xs.length === 0) { return acc + x[0] + x[1] }

        return aux(xs, acc + x[0] + x[1])
    }

    return aux(jogos)
}

console.log(
    pontuacao([1,2], [2,3], [3,4], [5,6], [2, 3], [1,1], [2,3])
)
