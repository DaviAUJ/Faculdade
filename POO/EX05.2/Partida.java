import java.util.Scanner;

public class Partida {
    private static void p_Jogar(Apertadinho jogo) {
        Scanner entrada = new Scanner(System.in);
        int chute;
        boolean estaCorreto;

        jogo.iniciar();

        while(true) {
            System.out.printf("Digite seu chute: ");
            chute = entrada.nextInt();

            
            
            estaCorreto = jogo.receberChute(chute);
            if(estaCorreto) { break; }
            
            System.out.println("Chute Errado");
        }

        System.out.println("Chute Correto");
    }

    private static void p_Config(Apertadinho jogo) {
        System.out.println("Valores atuais");
        System.out.println("Minimo: " + jogo.inicio);
        System.out.println("Maximo: " + jogo.fim);
    }

    private static void p_Sair() {
        
    }
    
    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);
        int escolha;

        System.out.println("1 - Jogar");
        System.out.println("2 - Configuracoes");
        System.out.println("3 - Sair");
        System.out.printf("\nEscolha: ");
        escolha = entrada.nextInt();
        
        Apertadinho jogo = new Apertadinho(0, 10);

        switch(escolha) {
        case 1 -> p_Jogar(jogo); 
        case 2 -> p_Config(jogo);
        case 3 -> p_Sair();
        }
    }
}
