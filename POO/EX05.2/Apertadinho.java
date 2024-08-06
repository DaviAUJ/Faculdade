public class Apertadinho {
    private static int randint(int min, int max) {
        double output = (Math.random() * (max - min + 1) + min);
        return (int) output;
    }

    private int NUMERO_SECRETO;
    public int inicio;
    public int fim;
    
    public Apertadinho(int inicio, int fim) {
        this.inicio = inicio;
        this.fim = fim;
    }

    public void iniciar() {
        NUMERO_SECRETO = randint(inicio, fim);
    }

    
    
    public boolean receberChute(int chute) { return chute == NUMERO_SECRETO; }
}