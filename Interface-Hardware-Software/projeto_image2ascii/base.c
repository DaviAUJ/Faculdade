#include <stdio.h>

FILE* INPUT;

int sum10(int in) {
	int saida = in;
	saida += 10;
	return saida;
}

int getDec() {
	int saida;

	fscanf(INPUT, "%d ", &saida);

	return saida;
}

int main(int argc, char *argv[]) {
	int teste;

	scanf("%X", &teste);
	printf("%d", teste);

	return 0;
}
