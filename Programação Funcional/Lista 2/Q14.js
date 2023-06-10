function nomearAlgarismo(num) {
    const nomes = {
        1: "Um",
        2: "Dois",
        3: "Três",
        4: "Quatro",
        5: "Cinco",
        6: "Seis",
        7: "Sete",
        8: "Oito",
        9: "Nove",
        0: "Zero"
    }

    if(num > 9 || num < 0) { return "Error" }
    else { return nomes[num] }
}

console.log(nomearAlgarismo(-9))