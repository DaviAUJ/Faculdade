const mmc = (m, n, mfixo=m, nfixo=n) => {
    if(m === n) { return m }
    
    if(m < n) { return mmc(m + mfixo, n, mfixo, nfixo) }
    if(m > n) { return mmc(m, n + nfixo, mfixo, nfixo) }
}

console.log(mmc(852, 498))