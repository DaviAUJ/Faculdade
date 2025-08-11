public class Data {
    private byte[] diasMaxMeses = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    private byte dia = 1;
    private byte mes = 1;
    private short ano = 1;

    public Data() {  }
    
    public Data(byte dia, byte mes, short ano) {
        // Limitando o ano
        if(ano >= 1) {
            this.ano = ano;
        }

        if(this.isBisexto()) {
            diasMaxMeses[1] = 29;
        }

        // Limitando o mes
        if(mes > 12) {
            this.mes = 12;
        }
        else if(mes >= 1) {
            this.mes = mes;
        }

        // Limitando dia
        if(dia > diasMaxMeses[mes]) {
            this.dia = diasMaxMeses[mes];
        }
        else if(dia >= 1) {
            this.dia = dia;
        }
    }

    public void setDia(byte dia) {
        // Limitando dia
        if(dia > diasMaxMeses[mes]) {
            this.dia = diasMaxMeses[mes];
        }
        else if(dia >= 1) {
            this.dia = dia;
        }
        else {
            this.dia = 1;
        }
    }

    public byte getDia() {
        return dia;
    }

    public void setMes(byte mes) {
        // Limitando o mes
        if(mes > 12) {
            this.mes = 12;
        }
        else if(mes >= 1) {
            this.mes = mes;
        }
        else {
            this.mes = 1;
        }
    }

    public byte getMes() {
        return mes;
    }

    public void setAno(short ano) {
        // Limitando o ano
        if(ano >= 1) {
            this.ano = ano;
        }
        else {
            this.ano = 1;
        }
    }

    public short getAno() {
        return ano;
    }

    public void setAll(byte dia, byte mes, short ano) {
        this.setDia(dia);
        this.setMes(mes);
        this.setAno(ano);
    }

    // Verificando se é ano bisexto
    public boolean isBisexto() {
        return ano % 400 == 0 ||(ano % 4 == 0 && ano % 100 != 0);
    }

    public String formatado() {
        return (dia + "/" + mes + "/" + ano);
    }
}
