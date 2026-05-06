String.prototype.isSubstring = function(string) {
    if(this.length === 0) { return '' }
    
    const stringMin = this.toLowerCase()
    const inputMin = string.toLowerCase()

    const aux = ([x, ...xs], index=0) => {
        if(index > inputMin.length - 1) { return true }
        if(xs.length === 0) {
            if(x === inputMin[inputMin.length - 1] && index === inputMin.length - 1) { return true }
            
            return false
        }

        if(x === inputMin[index]) { return aux(xs, index + 1)}
        return aux(xs, index)
    }

    return aux(stringMin)
}

console.log(
    'Fish & Chipz'.isSubstring("shipx")
)