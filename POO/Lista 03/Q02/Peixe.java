public class Peixe extends Humano{
    public Peixe() {
        massa = 0;
        tamanho = "";
    }
    
    public Peixe(float massa, String tamanho) {
        this.massa = massa;
        this.tamanho = tamanho;
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
