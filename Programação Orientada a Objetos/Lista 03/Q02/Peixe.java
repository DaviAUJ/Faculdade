public class Peixe extends Humano{
    public Peixe() {
        super();
    }
    
    public Peixe(float massa, String tamanho) {
        super(massa, tamanho);
    }

    @Override
    public void comunicar() {
        System.out.println("glub glub");
    }

    @Override
    public void movimentar() {
        System.out.println("Nadando");
    }
}
