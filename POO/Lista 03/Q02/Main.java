public class Main {
    public static void main(String[] args) {
        Peixe peixe = new Peixe(3.5f, "Medio");
        Passaro passaro = new Passaro(0.7f, "Pequeno");
        Humano humano = new Humano(110f, "Grande");

        System.out.println("\nPeixe:");
        System.out.println("Peso: " + peixe.getMassa() + "kg");
        System.out.println("Tamanho: " + peixe.getTamanho());
        peixe.comunicar();
        peixe.movimentar();

        System.out.println("\nPássaro:");
        System.out.println("Peso: " + passaro.getMassa() + "kg");
        System.out.println("Tamanho: " + passaro.getTamanho());
        passaro.comunicar();
        passaro.movimentar();
        
        System.out.println("\nHumano:");
        System.out.println("Peso: " + humano.getMassa() + "kg");
        System.out.println("Tamanho: " + humano.getTamanho());
        humano.comunicar();
        humano.movimentar();
    }
}
