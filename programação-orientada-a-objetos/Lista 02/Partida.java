import java.util.Scanner;

@SuppressWarnings("resource")
public class Partida {
    private static void p_Jogar(Apertadinho jogo) {
        Scanner entrada = new Scanner(System.in);
        int chute;
        int estaCorreto;

        jogo.iniciar();

        OUTER:
        while(true) {
            System.out.println("\n");
            jogo.mostrarIntervaloTemp();
            System.out.printf("\n\nDigite seu chute: ");
            chute = entrada.nextInt();
            estaCorreto = jogo.receberChute(chute);

            switch(estaCorreto) {
                case 1 -> { break OUTER; }
                case 2 -> System.out.println("\nChute fora do intervalo; Tente novamente");
                default -> {
                    jogo.mudarIntervaloTemp(chute);
                    System.out.println("\nChute Errado");
                }
            }
        }

        System.out.println("\nParabens você acertou o numero secreto");
    }

    private static void p_Config(Apertadinho jogo) {
        Scanner entrada = new Scanner(System.in);
        int escolha;

        do {
            System.out.println("\n\nValores atuais");
            System.out.println("Minimo: " + jogo.getMinimo());
            System.out.println("Maximo: " + jogo.getMaximo());

            System.out.println("\n1 - Ajustar valores");
            System.out.println("2 - Restaurar padrao");
            System.out.println("3 - Sair");

            System.out.printf("\nEscolha: ");
            escolha = entrada.nextInt();

            switch(escolha) {
                case 1 -> {
                    System.out.printf("\nValor Minimo: ");
                    jogo.setMinimo(entrada.nextInt());
                    System.out.printf("Valor Maximo: ");
                    jogo.setMaximo(entrada.nextInt());

                    System.out.println("\nValores alterados");
                }
                case 2 -> {
                    jogo.setMinimo(0);
                    jogo.setMaximo(100);

                    System.out.println("\nValores retornados ao padrao");
                }
                case 3 -> { System.out.println("\nRetornando ao menu inicial"); }
            } 

        } while(escolha != 3);
    }

    private static void p_Sair() {
        System.out.println("\n\nAte a proxima");
        System.out.println("Desligando...");
    }
    
    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);
        int escolha;

        Apertadinho jogo = new Apertadinho(0, 100);

        do {
            System.out.println("\n\n----- BEM-VINDO AO APERTADINHO -----");

            System.out.println("\n1 - Jogar");
            System.out.println("2 - Configuracoes");
            System.out.println("3 - Sair");
            System.out.printf("\nEscolha: ");
            escolha = entrada.nextInt();

            switch(escolha) {
            case 1 -> p_Jogar(jogo); 
            case 2 -> p_Config(jogo);
            case 3 -> p_Sair();
            }

        } while(escolha != 3);
    }
}
