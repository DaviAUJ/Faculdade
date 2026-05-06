const { print } = require("../abbb.js")

const tamanho = (string) => {
    if(string === '') { return 0 }

    return tamanho(string.slice(0, -1)) + 1
}

print(tamanho("asdasdasd"))