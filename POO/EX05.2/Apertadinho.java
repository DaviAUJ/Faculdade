public class Apertadinho {
    private static int randint(int min, int max) {
        double output = (Math.random() * (max - min + 1) + min);
        return (int) output;
    }

    private int NUMERO_SECRETO;
    private int minimo;
    private int maximo;
    public int minTemp;
    public int maxTemp;
    
    public Apertadinho(int minimoPadrao, int maximoPadrao) {
        this.minimo = minimoPadrao;
        this.maximo = maximoPadrao;
    }

    public void iniciar() {
        NUMERO_SECRETO = randint(minimo, maximo);
        minTemp = minimo;
        maxTemp = maximo;
    }

    public boolean receberChute(int chute) { return chute == NUMERO_SECRETO; }

    public void setMinimo(int novoValor) { minimo = novoValor; }

    public void setMaximo(int novoValor) { maximo = novoValor; }
}