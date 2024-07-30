import java.util.Scanner;

public class Q2 {
    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);

        System.out.printf("Digite um número: ");
        int n1 = entrada.nextInt();
        System.out.printf("Digite outro número: ");
        int n2 = entrada.nextInt();

        int soma = 0;
        for(int i = n1 + 1; i < n2; i++) { soma += i; }

        System.out.printf("A soma dos números entre %d e %d é %d", n1, n2, soma);
    }
}