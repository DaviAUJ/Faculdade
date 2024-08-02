import java.util.Scanner;

class Apertadinho {
    public static int randint(int min, int max) {
        double output = (Math.random() * (max - min) + min);
        return (int) output;
    }

    private int inicio;
    private int fim;
    private int numeroEscolhido;
    
    Apertadinho(int inicio, int fim) {
        this.inicio = inicio;
        this.fim = fim;
        this.numeroEscolhido = randint(inicio, fim);
    }
    
    public boolean adivinhar(int chute) { return chute == this.numeroEscolhido; }
}

public class Partida {
    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);
        int escolha;

        System.out.println("1 - Jogar");
        System.out.println("2 - Configuracoes");
        System.out.println("3 - Sair");
        System.out.printf("\nEscolha: ");
        escolha = entrada.nextInt();
        /*
        switch(escolha) {
        case 1: p_Jogar();
        case 2: p_Config();
        case 3: p_Sair();
        }*/
    }
}
