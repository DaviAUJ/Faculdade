import java.util.Scanner;

class aux {
    public static int randint(int min, int max) {
        double output = (Math.random() * (max - min) + min);
        return (int) output;
    }

    public static void p_Jogar(Apertadinho jogo) {
        
    }

    public static void p_Config(Apertadinho jogo) {
        
    }

    public static void p_Sair(Apertadinho jogo) {
        
    }
}

class Apertadinho {
    int inicio;
    int fim;
    private int numeroEscolhido;
    
    public Apertadinho(int inicio, int fim) {
        this.inicio = inicio;
        this.fim = fim;
        this.numeroEscolhido = aux.randint(inicio, fim);
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
