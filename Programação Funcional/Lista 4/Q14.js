const repita = (string, vezes) => {
    if(vezes === 1) { return string }

    return repita(string, vezes - 1) + string
}

console.log(
    repita("abc", 50)
)