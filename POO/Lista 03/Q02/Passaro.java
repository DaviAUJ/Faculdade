public class Passaro extends Humano {
    public Passaro() {
        massa = 0;
        tamanho = "";
    }
    
    public Passaro(float massa, String tamanho) {
        this.massa = massa;
        this.tamanho = tamanho;
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
