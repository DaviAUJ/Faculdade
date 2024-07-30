
import java.util.Scanner;

public class Q3 {
    public static void main(String[] args) {
        Scanner entrada = new Scanner(System.in);

        System.out.printf("Digite um valor: ");
        int n = entrada.nextInt();

        float soma = 0;
        for(int i = 1; i <= n; i++) { soma += 1f / i; }

        System.out.printf("A soma será: %f", soma);
    }
}