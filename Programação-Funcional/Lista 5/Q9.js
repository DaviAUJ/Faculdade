const { composite, log, range, sum, equals, indef } = require('./utils.js')

function contarCaracteres (string) { 
    return string.split("").filter(
        (item) => item === " " ? "" : item
    ).length
}

function extenso(num) {
    if(num > 1000 || num < 0) { return "Número excedente" }

    const algarismos = [
        "", // Zero
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine"
    ]
    
    const entre9e20 = [
        "ten",
        "eleven",
        "twelve",
        "thirteen",
        "fourteen",
        "fifteen",
        "sixteen", 
        "seventeen",
        "eighteen",
        "nineteen"
    ]
    
    const dezenas = [
        "twenty",
        "thirty",
        "fourty",
        "fifty",
        "sixty",
        "seventy",
        "eighty",
        "ninety",
    ]

    // Processamento do número extenso
    const numList = num.toString().split("").reverse()

    const output = numList.map(
        (item, index) => {
            const int = parseInt(item)

            if(index === 0 && numList[1] === "1") { return "" } 

            if(index === 0) { return algarismos[int] }
            if(index === 1) {
                if(int === 0) { return "" }
                if(int === 1) { return entre9e20[parseInt(numList[0])] }

                return dezenas[int - 2] 
            }

            if(index === 2) {
                if(int === 0) { return "" }
                
                return `${algarismos[int]} hundred`
            }

            if(index === 3) {
                return "one thousand"
            }
        }
    ).reverse().join(" ")

    return [
        output,
        contarCaracteres(output)
    ]
}

log(
    extenso(123)
)