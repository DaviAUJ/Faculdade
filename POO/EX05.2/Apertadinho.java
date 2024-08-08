public class Apertadinho {
    private static int randint(int min, int max) {
        double output = (Math.random() * (max - min + 1) + min);
        return (int) output;
    }

    private int numSecreto;
    private int minimo;
    private int maximo;
    public int minTemp;
    public int maxTemp;
    
    public Apertadinho(int minimoPadrao, int maximoPadrao) {
        this.minimo = minimoPadrao;
        this.maximo = maximoPadrao;
    }

    public void iniciar() {
        numSecreto = randint(minimo, maximo);
        minTemp = minimo;
        maxTemp = maximo;
    }

    public void mostrarIntervaloTemp() {
        int minDiff = minTemp - minimo;
        int divisor = (maximo - minimo) / 40;
        int i = String.valueOf(minTemp).length() - 1;

        while(i < minDiff / divisor) { 
            System.out.printf(" "); 
            i++;
        }
        System.out.printf("%d | ", minTemp);

        while(i < maxTemp / divisor) { 
            System.out.printf("-"); 
            i++;
        }
        System.out.printf(" | %d", maxTemp);
    }

    public int receberChute(int chute) { 
        if(chute > maxTemp || chute < minTemp) { return 2; }
        if(chute == numSecreto) { return 1; }
        else { return 0; } 
    }

    public void mudarIntervaloTemp(int chute) {
        if(chute < numSecreto) { minTemp = chute; }
        else if(chute > numSecreto) { maxTemp = chute; }
    }

    public void setMinimo(int novoValor) { minimo = novoValor; }

    public void setMaximo(int novoValor) { maximo = novoValor; }

    public int getMinimo() { return minimo; }

    public int getMaximo() { return maximo; }
}