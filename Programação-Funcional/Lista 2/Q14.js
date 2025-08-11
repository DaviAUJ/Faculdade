const nomearAlgarismo = (num) => {
    const nomes = [
        "Um",
        "Dois",
        "Três",
        "Quatro",
        "Cinco",
        "Seis",
        "Sete",
        "Oito",
        "Nove",
        "Zero"
    ]

    // Verificação se o input é válido
    if(num > 9 || num < 0) { return "Error" }
    else { return nomes[num - 1] }
}

console.log(nomearAlgarismo(5))