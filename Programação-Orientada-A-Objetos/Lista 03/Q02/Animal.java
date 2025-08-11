public abstract class Animal {
    private float massa;
    private String tamanho;
    
    protected Animal() {
        massa = 0;
        tamanho = "";
    }
    
    protected Animal(float massa, String tamanho) {
        this.massa = massa;
        this.tamanho = tamanho;
    }
    
    public void setMassa(float massa) {
        this.massa = massa;
    }

    public float getMassa() {
        return massa;
    }

    public void setTamanho(String tamanho) {
        this.tamanho = tamanho;
    }

    public String getTamanho() {
        return tamanho;
    }

    public abstract void movimentar();

    public abstract void comunicar(); 
}
