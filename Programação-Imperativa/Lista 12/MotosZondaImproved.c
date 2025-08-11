#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define tamNome 20
#define tamModelo 10
#define tamPlaca 6
#define tamDefeito 50

typedef struct data{
    unsigned int dia;
    unsigned int mes;
    unsigned int ano;
    float ganhos;

} data;

typedef struct RegMoto{
	char Nome[tamNome + 1];
	char Modelo[tamModelo + 1];
	char Placa[tamPlaca + 1];
	char Defeito[tamDefeito + 1];
	char Status;
	float Preco;

} TpRegMoto;

TpRegMoto VZonda[50];

char nomeArquivoMotos[tamNome + 1] = "motosPendentes.dat";
char nomeArquivoFinanceiro[tamNome + 1] = "financeiro.dat";
FILE* arquivoMotos;
FILE* arquivoFinanceiro;

unsigned int tamanhoData = 3 * sizeof(unsigned int) + sizeof(float);
unsigned int tamanhoRegMoto = (tamNome + tamModelo + tamPlaca + tamDefeito + 6) * sizeof(char) + sizeof(float);

int Quant = -1; //Controla o preenchimento do vetor

data dia;

long int TArquivo(FILE* arquivo, unsigned int tamanhoCelula) {
    fseek(arquivo, 0, 2);

	long int R = ftell(arquivo) / tamanhoCelula;

	return R;
}

TpRegMoto pegaUltimoRegistro(FILE* arquivo, unsigned int tamanho) {
    TpRegMoto output;

    if(TArquivo(arquivo, tamanho) == 0) {
        strcpy(output.Nome, "INVALIDO");
        output.Preco = -1;

        return output;
    }

    // Vai pro final do arquivo
    fseek(arquivo, -tamanho, 2);

    // Pega o ultimo registro
    fread(&output, tamanho, 1, arquivo);

    return output;
}

data pedirData() {
    data output;

    printf("\nDigite a data de hoje\n");
    printf("\ndia: ");
    scanf("%i", &output.dia);

    printf("mes: ");
    scanf("%i", &output.mes);

    printf("ano: ");
    scanf("%i", &output.ano);

    return output;
}   

void SolicitaServico() {
    /* (1) Solicitar Serviço – quando se insere os dados supracitados, e também os campos status com valor zero sinalizando que o serviço ainda não foi feito, preço, também iniciado com zero.  Este deve estar em loop. */
    char Sair = 'S';
  
    do {
        printf("\n\n >>> Motos Zonda <<< \n\n");

        Quant++;

        printf("Qual o nome do cliente? ");
        scanf(" %[^\n]s", VZonda[Quant].Nome);

        printf("Qual o modelo da moto? ");
        scanf(" %[^\n]s", VZonda[Quant].Modelo);

        while(1) {
            printf("Qual a placa da moto? ");
            scanf(" %[^\n]s", VZonda[Quant].Placa);

            if(strlen(VZonda[Quant].Placa) == tamPlaca) {
                int jaExiste = 0;

                for(int Cont = 0; Cont < Quant; Cont++) {
                    if(strcmp(VZonda[Cont].Placa, VZonda[Quant].Placa) == 0) { jaExiste = 1; }
                }

                if(jaExiste == 0) { break; }
                else { printf("Esta placa ja existe no sistema\n\n"); }

            } else { printf("Placa de tamanho incorre - digite novamente\n\n"); }
        }

        printf("Qual o defeito da moto? ");
        scanf(" %[^\n]s", VZonda[Quant].Defeito);

        printf("Preco estimado do servico: R$");
        scanf("%f", &VZonda[Quant].Preco);

        VZonda[Quant].Status = '0';
        
        printf("\n\nDeseja inserir novo servico(S|N)? ");
        scanf(" %c",&Sair);

        Sair = toupper(Sair);

    } while(Sair != 'N');
}

void IniciaServico() {
    /*(2) Iniciar Serviço – quando o status de uma dada moto (placa) é iniciado pelo mecânico e o status para a ser um.*/

    char P[tamPlaca + 1];

    while(1) {
        printf("Placa da moto para iniciar servico: ");
        scanf(" %[^\n]s", P);

        if(strlen(P) == tamPlaca) { break; }

        printf("Placa incompleta - digite novamente\n\n");
    }
    
    int Pos = -1; //posição da moto P no vetor
    
    //busca da moto para iniciar serviço
    for(int Cont = 0; Cont <= Quant; Cont++) {
        if(strcmp(VZonda[Cont].Placa, P) == 0) { Pos = Cont; }
    }

    char escolha;
        
    if(Pos == -1) { printf("Moto nao cadastrada!\n"); }
    else if(VZonda[Pos].Status == '0'){
        printf("\n Cliente %d: %s", Pos+1, VZonda[Pos].Nome);
        printf("\n Modelo: %s", VZonda[Pos].Modelo);
        printf("\n Placa: %s", VZonda[Pos].Placa);
        printf("\n Defeito: %s", VZonda[Pos].Defeito);
        printf("\n Status: %c",VZonda[Pos].Status);
        printf("\n Preco estimado: R$%.2f\n", VZonda[Pos].Preco); 
        
        VZonda[Pos].Status = '1';
    }
    else if(VZonda[Pos].Status == '1') { printf("Servico ja iniciado\n"); }
    else if(VZonda[Pos].Status == '2') { 
        printf("Deseja retirar o cancelamento do servico(S/N)? ");
        scanf(" %c", &escolha);

        if(toupper(escolha) == 'S') { VZonda[Pos].Status = '0'; }
        else { printf("Servico continua cancelado\n"); }

    } 
    else if(VZonda[Pos].Status == '3') { printf("Servico ja concluido\n"); }
    else { printf("ERRO: status de servico desconhecido - nada sera alterado\n"); }
}

void RemoverSolicitacao() {
    char P[tamPlaca + 1]; 

    while(1) {
        printf("Placa da moto para cancelar o servico: ");
        scanf(" %[^\n]s", P);

        if(strlen(P) == tamPlaca) { break; }

        printf("Placa incompleta - digite novamente\n\n");
    }
    
    int Pos = -1; //posição da moto P no vetor
    
    //busca da moto para iniciar serviço
    for(int Cont = 0; Cont <= Quant; Cont++) {
        if(strcmp(VZonda[Cont].Placa, P) == 0) { Pos = Cont; }
    }

    if(Pos == -1) { printf("Moto nao cadastrada!\n"); }
    else if(VZonda[Pos].Status == '0') {
        printf("Servico cancelado\n");

        VZonda[Pos].Status = '2';
    }
    else if(VZonda[Pos].Status == '1') { printf("Nao e possivel cancelar - servico em andamento\n"); }
    else if(VZonda[Pos].Status == '2') { printf("Servico ja foi cancelado\n"); }
    else if(VZonda[Pos].Status == '3') { printf("Servico ja concluido\n"); }
    else { printf("ERRO: status de servico desconhecido - nada sera alterado\n"); }
}

void ConsultarSolicitacoes() {
    printf("\n\n >>> Motos Zonda <<< \n\n");

    if(Quant == -1) { printf("Nao ha servicos cadastrados."); }
    else {
        for(int Cont = 0; Cont <= Quant; Cont++) {
            printf("\n Cliente %d: %s", Cont+1, VZonda[Cont].Nome);
            printf("\n Modelo: %s", VZonda[Cont].Modelo);
            printf("\n Placa: %s", VZonda[Cont].Placa);
            printf("\n Defeito: %s", VZonda[Cont].Defeito);
            printf("\n Status: %c",VZonda[Cont].Status);
            
            if(VZonda[Cont].Status == '3') { printf("\n Preco final: R$%.2f", VZonda[Cont].Preco); }
            else { printf("\n Preco estimado: R$%.2f", VZonda[Cont].Preco); }
    
            printf("\n --------------------- \n\n"); 
        }
    }
}

void ConcluirServico() {
    char P[tamPlaca + 1];

    while(1) {
        printf("Placa da moto para confirmar conclusao do servico: ");
        scanf(" %[^\n]s", P);

        if(strlen(P) == tamPlaca) { break; }

        printf("Placa incompleta - digite novamente\n\n");
    } 

    int Pos = -1; //posição da moto P no vetor
    
    //busca da moto para iniciar serviço
    for(int Cont = 0; Cont <= Quant; Cont++) {
        if(strcmp(VZonda[Cont].Placa, P) == 0) { Pos = Cont; }
    }

    if(Pos == -1) { printf("Moto nao cadastrada!\n"); }
    else if(VZonda[Pos].Status == '0') { printf("Servico ainda nao inicializado\n"); }
    else if(VZonda[Pos].Status == '1') {
        printf("Este servico agora esta concluido\n");

        VZonda[Pos].Status = '3';

        printf("\nDigite o preco final do servico: R$");
        scanf("%f", &VZonda[Pos].Preco);
    }
    else if(VZonda[Pos].Status == '2') { printf("Este servico esta cancelado\n"); }
    else if(VZonda[Pos].Status == '3') { printf("Este servico ja foi concluido\n"); }
    else { printf("ERRO: status de servico desconhecido - nada sera alterado\n"); }
}

void historico() {
    int quant = TArquivo(arquivoFinanceiro, tamanhoData);
    data seletor, melhorDia;

    // definindo o primeiro item como base de comparação
    fseek(arquivoFinanceiro, 0, 0);
    fread(&melhorDia, tamanhoData, 1, arquivoFinanceiro);
    fseek(arquivoFinanceiro, 0, 0); 
   
    printf("\n --------------------- \n\n"); 
    if(quant != 0) {
        for(int i = 0; i < quant; i++) {
            fread(&seletor, tamanhoData, 1, arquivoFinanceiro);
            
            // verificação para definir o melhor dia
            if(melhorDia.ganhos < seletor.ganhos) { melhorDia = seletor; }

            printf("Data: %02d / %02d / %04d\n", seletor.dia, seletor.mes, seletor.ano);
            printf("Ganhos: R$%.2f", seletor.ganhos);
            printf("\n\n --------------------- \n\n"); 
        }

    } else {
        printf("Nao existe nenhum registro");
        printf("\n\n --------------------- \n\n"); 
    }
}

int Opcao;

void EncerrarExpediente() {
    float soma = 0;

    // Limpa o arquivo para novos registros
    fclose(arquivoMotos);
    remove(nomeArquivoMotos);
    arquivoMotos = fopen(nomeArquivoMotos, "a+b");

    fseek(arquivoMotos, 0, 0);

    for(int i = 0; i <= Quant; i++) {
        if(VZonda[i].Status == '0' || VZonda[i].Status == '1') { fwrite(&VZonda[i], tamanhoRegMoto, 1, arquivoMotos); } 
        else if(VZonda[i].Status == '3') { 
            soma += VZonda[i].Preco;

            printf("Servico #%d - %s\n", i + 1, VZonda[i].Nome);
            printf("Placa: %s\n", VZonda[i].Placa);
            printf("Preco: %.2f\n\n", VZonda[i].Preco);
        }
    }

    printf("\nTotal ganho hoje: R$%.2f" , soma);

    // Passando os dados financeiros para o arquivo
    dia.ganhos = soma;

    fseek(arquivoFinanceiro, 0, 0);
    fwrite(&dia, tamanhoData, 1, arquivoFinanceiro);

    Opcao = -1;
}

void pegarServPendentes() {
    if(TArquivo(arquivoMotos, tamanhoRegMoto) != 0) {
        TpRegMoto temp, ultimo = pegaUltimoRegistro(arquivoMotos, tamanhoRegMoto);
        unsigned int index = 0;

        fseek(arquivoMotos, 0, 0);

        do {
            fread(&temp, tamanhoRegMoto, 1, arquivoMotos);
            VZonda[index] = temp;
            
            index++;
        } while(strcmp(temp.Nome, ultimo.Nome) != 0);

        Quant += index;
    }
}

int main() {
    arquivoMotos = fopen(nomeArquivoMotos, "a+b");
    arquivoFinanceiro = fopen(nomeArquivoFinanceiro, "a+b");

    system("cls");
    pegarServPendentes();
    dia = pedirData();

    do {
        //Exibicao de menu e leitura da opcao. 
        system("cls");	

        printf("\n >>> Motos Zonda <<< \n\n");

        printf("1 - Solicitar Servico \n");
        printf("2 - Iniciar Servico \n");
        printf("3 - Remover Solicitacao \n");
        printf("4 - Consultar Solicitacoes \n");
        printf("5 - Concluir Servico \n");
        printf("6 - Historico financeiro \n");
        printf("7 - Encerrar Expediente \n");

        printf("\nDigite a opcao desejada: ");
        scanf("%d", &Opcao);

        system("cls");

        switch(Opcao) {
            case 1: SolicitaServico(); break;
            case 2: IniciaServico(); break;
            case 3: RemoverSolicitacao(); break;
            case 4: ConsultarSolicitacoes(); break;
            case 5: ConcluirServico(); break;
            case 6: historico(); break;
            case 7: EncerrarExpediente(); break;
        }

        printf("\n");
        system("pause");

    } while(Opcao != -1);

    return 0;
}
