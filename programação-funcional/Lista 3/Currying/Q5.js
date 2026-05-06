const medirDistancia = (x1) => (y1) => (x2) => (y2) => {
    if(x1 === x2) { return Math.abs(y2 - y1) } 
    if(y1 === y2) { return Math.abs(x2 - x1) }
    
    return ((x2 - x1) ** 2 + (y2 - y1) ** 2) ** (1/2)
}

console.log(
    medirDistancia(3)(5)(2)(6)
)