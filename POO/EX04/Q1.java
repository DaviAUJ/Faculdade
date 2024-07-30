import java.util.Scanner;

public class Q1 {
    public static void main(String[] args) {
        Scanner dado = new Scanner(System.in);
        
        System.out.println("Seja bem-vindo ao parque de diversão Avaj!");
        System.out.printf("Digite sua altura em metros: ");
        float altura = dado.nextFloat();
        System.out.printf("Digite sua idade: ");
        int idade = dado.nextInt();

        if(altura > 1.5f && idade >= 18) { System.out.println("Você pode entrar no brinquedo"); }
        else { System.out.println("Infelizmente você não pode entrar no brinquedo"); }
    }
}