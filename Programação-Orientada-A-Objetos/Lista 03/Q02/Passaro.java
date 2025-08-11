public class Passaro extends Humano {
    public Passaro() {
        super();
    }
    
    public Passaro(float massa, String tamanho) {
        super(massa, tamanho);
    }

    @Override
    public void comunicar() {
        System.out.println("Cantando");
    }

    @Override
    public void movimentar() {
        System.out.println("Voando");
    }
}
