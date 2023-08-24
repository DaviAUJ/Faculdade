const inverte = (string, acc=0) => {
    if(acc === string.length) { return '' }

    return inverte(string, acc + 1) + string[acc]
}

console.log(inverte("davi"))