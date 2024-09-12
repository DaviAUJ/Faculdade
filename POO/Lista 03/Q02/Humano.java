public class Humano extends Animal {
    public Humano() {
        super();
    }
    
    public Humano(float massa, String tamanho) {
        super(massa, tamanho);
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
