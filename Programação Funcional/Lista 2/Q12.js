function quadFunction(a, b, c) {
    const x = [
        (-b + (b ** 2 - 4 * a * c) ** (1/2)) / (2 * a),
        (-b - (b ** 2 - 4 * a * c) ** (1/2)) / (2 * a)
    ]
    
    return x
}

console.log(quadFunction(1, 6, -7))