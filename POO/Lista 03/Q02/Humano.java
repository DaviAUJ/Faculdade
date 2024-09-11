public class Humano extends Animal {
    public Humano() {
        massa = 0;
        tamanho = "";
    }
    
    public Humano(float massa, String tamanho) {
        this.massa = massa;
        this.tamanho = tamanho;
    }

    @Override
    public void movimentar() {
        System.out.println("Andando");
    }

    @Override
    public void comunicar() {
        System.out.println("Falando");
    }
}
