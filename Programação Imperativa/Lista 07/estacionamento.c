/* 
Considerando a necessidade de construir um programa para definir o 
valor a pagar pelo uso de um vaga de estacionamento, por tempo de 
uso. Onde: as vagas são numeradas, o cliente escolhe a vaga em que 
deseja estacionar seu carro, é registrado no sistema a hora de che-
gada no estacionamento; exemplo, se um carro chegou às 8:00 no es-
tacionamento e ocupa a vaga 15, na posição 15 do vetor é armazenada
a string Placa + hora.
Você decide e implementa as operações a serem disponibilizados ao 
usuário do programa, a necessidade de aplicar subprograma e o valor 
pela unidade de tempo de uso do estacionamento.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Função feita no exercicio 5 da lista 6
int compararStr(char* str1, char* str2) {
    int tamanho1 = strlen(str1), tamanho2 = strlen(str2);

    if(tamanho1 != tamanho2) { return 0; }

    for(int cont = 0; cont <= tamanho1; cont++) {
        if(str1[cont] != str2[cont]) { return 0; }
    }

    return 1;
}

char Estaciona[31][14]; //30 vagas e mantem placa com 7 caracteres, sinal de + e 5 caracteres para hora
int qCarrosHora[14], hMovimentada;
float Valor, ganhos = 0;
char Responsavel[21] = "", Iniciou = 0;

void AbrirCaixa() {
    system("cls");
    system("color 80"); // 8 - cinza  0 - preto

    printf("\n >>> Estacionamento <<< \n");
    printf(" >>>  Largas Vagas  <<< \n");
    printf("\n     ABRINDO  CAIXA \n");   

    for (int i = 0; i < 30; i++) { strcpy(Estaciona[i], "LIVRE"); }

    printf("\nQual o valor do estacionamento por hora de uso? ");
    scanf("%f", &Valor);

    fflush(stdin);

    printf("Qual o nome do responsavel? ");
    gets(Responsavel);
    
    Iniciou=1;
}

void ClienteChega() {
    int Vaga;
    char Placa[8] = "", horario[6] = "", Entrada[14] = "";

    // Variáveis exercício 3
    int hora;

    system("cls");
    system("color 80"); // 8 - cinza  0 - preto

    printf("\n >>> Estacionamento <<< \n");
    printf(" >>>  Largas Vagas  <<< \n");
    printf("\n   CHEGADA DE CLIENTE \n");   

    if (Iniciou) {
        printf("\n CAIXA ABERTO   Valor/h: %.2f", Valor);
        printf("\n Responsavel: %s\n\n", Responsavel);

        fflush(stdin);

        printf("Qual a horario de entrada [formato hh:mm]? ");
        gets(horario);

        // Exercício 3 & 4
        hora = 10 * (horario[0] - '0') + (horario[1] - '0');

        if(hora >= 6 && hora < 20) {
            printf("Qual a vaga ocupada? ");
            scanf("%d", &Vaga);

            fflush(stdin);

            printf("Qual a placa do veiculo [7 digitos]? ");
            gets(Placa);
            strcpy(Entrada, Placa);

            printf("Chegada registrada com sucesso!\n\n");

            // -6 para mudar o index para o primeiro
            qCarrosHora[hora - 6]++;
            strcat(Entrada, "+");
            strcat(Entrada, horario);
            strcpy(Estaciona[Vaga-1], Entrada);

        } else {
            printf("No momento o estaciomento esta fechado\n\n");

        }
        
    } else { printf("\nERRO: Antes eh preciso abrir o caixa!\n"); }
    
    system("pause");
}

void ClienteSai() {
    char Placa[8] = "", Entrada[14] = "", Hora[3] = "", Min[3] = "";
    int Vaga;
    int H, M; //hora, minuto e segundo

    // Variáveis exercício 2
    char horarioSaida[6]; // hh:mm
    int deltaTempo, hSaida, mSaida;
    float preco = 0, valorPago;

    system("cls");
    system("color 80"); // 8 - cinza  0 - preto

    printf("\n >>> Estacionamento <<< \n");
    printf(" >>>  Largas Vagas  <<< \n");
    printf("\n    SAIDA DE CLIENTE \n");   

    if (Iniciou) {
        printf("\n CAIXA ABERTO   Valor/h: %.2f", Valor);
        printf("\n Responsavel: %s\n\n", Responsavel);

        printf("Qual a vaga ocupada? ");
        scanf("%d", &Vaga);
        
        //se vaga LIVRE, houve erro
        strcpy(Entrada, Estaciona[Vaga - 1]);
        
        //Teste
        printf("\n>>>>>>>%s\n", Entrada);
    
        for(int i = 0; i < 7; i++) { Placa[i] = toupper(Entrada[i]); }
        
        // Se estiver livre não faz nada
        if(!compararStr(Entrada, "LIVRE")) {
            //Teste
            printf(">>>>>>>Placa: %s", Placa);
            
            Hora[0] = Entrada[8];
            Hora[1] = Entrada[9];
            Hora[2] = '\0';
            H = atoi(Hora); // convete string em inteiro

            Min[0] = Entrada[11];
            Min[1] = Entrada[12];
            Min[2] = '\0';
            M = atoi(Min); // convete string em inteiro
            
            //Teste
            printf("\n>>>>>>>Hora: %d",H);
            printf("\n>>>>>>>Minutos: %d\n",M);

            // >> Exercício 2 <<
            printf("\nQue horas o cliente saiu(hh:mm)? ");
            scanf("%s", horarioSaida);

            // conversão para inteiro
            // por ascii essa subtração transforma um numero em char para inteiro, 10 * é para colocar um deles no casa das dezenas
            // E a hora é convertida em minuto para calculo mais fácil
            hSaida = 10 * (horarioSaida[0] - '0') + (horarioSaida[1] - '0');
            mSaida = 10 * (horarioSaida[3] - '0') + (horarioSaida[4] - '0');
            deltaTempo = (hSaida * 60 + mSaida) - (H * 60 + M);

            // O meu sistema pagamento será
            // tempo <= 30min não paga
            // apos esse tempo 1 hora custa o valor informado no caixa
            // e a cada 15 min extra será cobrado 1/6 do valor da hora
            if(deltaTempo <= 30) { printf("Nao havera cobranca\n\n"); }
            else {
                preco += (deltaTempo / 60) * Valor;
                deltaTempo %= 60;

                preco += (deltaTempo / 15) * (Valor / 6);

                // Exercício 5
                ganhos += preco;

                printf("Preco do estacionamento: R$%.2f\n\n", preco);

                printf("\nValor pago pelo cliente: R$");
                scanf("%f", &valorPago);


                if(valorPago == preco) {
                    printf("\nPagamento efetuado - Nao e necessario troco\n\n");

                } else {
                    printf("\nPagamento efetuado - troco: R$%.2f\n\n", valorPago - preco);
                    
                }
            }

            // retira o cliente da vaga
            strcpy(Estaciona[Vaga - 1], "LIVRE");
        }

    } else { printf("\nERRO: Antes eh preciso abrir o caixa!\n"); }
        
    system("pause");
}

int Op;

void FecharCaixa() {
    // Exercício 3
    int podeFechar = 1, horario;

    system("cls");
    system("color 70"); // 8 - cinza  0 - preto

    // Verifica se pode fecahr
    for(int cont = 0; cont < 30; cont++) {
        // Se for diferente de "LIVRE"
        if(!compararStr(Estaciona[cont], "LIVRE")) {
            podeFechar = 0;
            
            printf(" Ha um carro na vaga #%d\n", cont + 1);
        }
    }

    if(podeFechar) {
        for(int cont = 0; cont < 14; cont++) {
            horario = cont + 6;

            printf(" %d:00 - %d\n", horario, qCarrosHora[cont]);

            // Exercício 5
            if(cont == 0 || qCarrosHora[cont] > qCarrosHora[hMovimentada - 6]) { hMovimentada = horario; }
        }

        printf("Ganhos do dia: R$%.2f\n", ganhos);
        printf("Horario mais movimentado: %d:00\n", hMovimentada);
        printf("\n O caixa foi fechado\n\n");
        Op = 5;

    } else { 
        printf("\n O caixa nao pode ser fechado\n\n"); 

        system("pause");
    }
}

int main(){
    do {
        system("cls");
        system("color 70"); // 7 - branco  0 - preto

        printf("\n >>> Estacionamento <<< \n");
        printf(" >>>  Largas Vagas  <<< \n");
        printf("\n 1 - Abrir Caixa");
        printf("\n 2 - Chegada de Cliente");
        printf("\n 3 - Saida de Cliente");
        printf("\n 4 - Fechar Caixa");
        // 5 - Se tudo ocorrer bem com a saída a opção 4 muda Op para 5 para pode finalizar
        printf("\n\n Qual a opcao desejada? ");

        do {
            scanf("%d",&Op);

            if(Op < 1 || Op > 4) {
                printf("\n ERRO: Opcao invalida!");
                printf("\n Qual a opcao desejada? ");

            } else { break; }
                
        } while(1);
        
        switch(Op) {
            case 1: AbrirCaixa();
                break;

            case 2: ClienteChega();
                break;

            case 3: ClienteSai();
                break;
                
            case 4: FecharCaixa();
                break;
        }
    } while(Op != 5);
        
    return 0;
}