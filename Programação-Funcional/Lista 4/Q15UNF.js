const arrayShift = (array) => array.map(
    (x, index) => {
        if(index === 0) { return array[array.length - 1] }

        return array[index - 1]
    }
)

const caminhos = (...args) => {
    if(args.length === 1) { return args[0] }

    return caminhos(...args) + ` -> ${args[args.length - 1]}`
}

console.log(caminhos(1, 2, 3, 4, 5))