import java.util.Scanner;

public class Partida {
    private static void p_Jogar(Apertadinho jogo) {
        Scanner entrada = new Scanner(System.in);
        int chute;
        boolean estaCorreto = false;

        jogo.iniciar();

        while(!estaCorreto) {
            System.out.println("Digite seu chute: ");
            chute = entrada.nextInt();
            
            estaCorreto = jogo.receberChute(chute);
        }
        
    }

    private static void p_Config() {
        
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
        
        Apertadinho jogo = new Apertadinho(0, 100);

        switch(escolha) {
        case 1: p_Jogar(jogo);
        case 2: p_Config();
        case 3: p_Sair();
        }
    }
}
