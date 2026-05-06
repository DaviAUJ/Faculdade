// Melhoria 1: Função de excluir todo um arquivo
// Melhoria 2: Função de escolher outro arquivo para ler e alterar
// Melhoria 3: Mensagem de confirmação na hora de apagar um registro
// Melhoria 4: Função de criar outro arquivo

#include <stdio.h>
#include <stdlib.h>  //usado system
#include <ctype.h>   //usado toupper
#include <string.h>  //usado strcmp

typedef struct TpFarma{
	char Nome[21];
	float Preco;
	int QEstoque;

} TpFarma;

TpFarma RgFarma;
FILE* ArqFarma;

long int Tamanho = 21 * sizeof(char) + sizeof(float) + sizeof(int);

long int TArquivo(FILE* arquivo) {
    fseek(arquivo, 0, 2);

	long int R = ftell(arquivo) / Tamanho;

	return R;
}

TpFarma pegaUltimoRegistro(FILE* arquivo) {
    TpFarma output;

    if(TArquivo(arquivo) == 0) {
        strcpy(output.Nome, "INVALIDO");
        output.Preco = -1;
        output.QEstoque = -1;

        return output;
    }

    // Vai pro final do arquivo
    fseek(arquivo, -Tamanho, 2);

    // Pega o ultimo registro
    fread(&output, Tamanho, 1, arquivo);

    return output;
}

int estaPresenteArquivo(FILE* arquivo, char* nome) {
    int output = 0;

    if(TArquivo(arquivo) == 0) { return output; }

    TpFarma ultimo = pegaUltimoRegistro(arquivo), temp;

    fseek(arquivo, 0, 0);

    do {
        fread(&temp, Tamanho, 1, arquivo);

        if(strcmp(temp.Nome, nome) == 0) { output = 1; break; }

    } while(strcmp(ultimo.Nome, temp.Nome) != 0);

    return output;
}

int arqExiste(char* nome) {
    FILE* arquivo;
    int output = 1;

    arquivo = fopen(nome, "r");

    if(arquivo == NULL) { output = 0; }

    fclose(arquivo);

    return output;
}

void Incluir() {
    char nomeTemp[21];
    char R, escolha = 'S';

    do {
        system("cls");

        printf("*** inclusao ***\n\n");
        
        while(escolha == 'S') {
            printf("Nome: ");
            scanf(" %s", nomeTemp);

            if(!estaPresenteArquivo(ArqFarma, nomeTemp)) { break; }

            printf("\nEste farmaco ja esta registrado");
            printf("\nDigitar outro nome(S/N)? ");
            scanf(" %c", &escolha);
            escolha = toupper(escolha);

            printf("\n");
        }
        
        if(escolha == 'S') {
            strcpy(RgFarma.Nome, nomeTemp);

            printf("Preco: R$");
            scanf("%f", &RgFarma.Preco);

            printf("Estoque: ");
            scanf("%d", &RgFarma.QEstoque);

            fseek(ArqFarma, 0, 2);
            fwrite(&RgFarma, Tamanho, 1, ArqFarma);

            printf("\nNova inclusao? S/N ");
            scanf(" %c", &R);

            R = toupper(R);
        } else { R = 'N'; }
    } while(R != 'N');
}

void Excluir() {
    if(TArquivo(ArqFarma) != 0) {
        TpFarma ultimo = pegaUltimoRegistro(ArqFarma);
        char Farmaco[21], escolha;
        int Achou = 0;

        fclose(ArqFarma); //modo a + b
        ArqFarma = fopen("Farmacos.dat", "r+b");

        system("cls");

        printf("*** Excluir ***\n\n");

        fseek(ArqFarma, 0, 0);

        printf("Qual farmaco? ");
        scanf("%s", Farmaco);

        do {
            fread(&RgFarma, Tamanho, 1, ArqFarma);

            if(strcmp(RgFarma.Nome, Farmaco) == 0) {
                Achou = 1;

                printf("\nNome: %s\n", RgFarma.Nome);
                printf("Valor: R$%.2f\n", RgFarma.Preco);
                printf("Estoque: %d\n", RgFarma.QEstoque);

                printf("\nTem certeza que quer deletar este registro(S/N)? ");
                scanf(" %c", &escolha);
            }
        } while(strcmp(ultimo.Nome, RgFarma.Nome) != 0 && Achou == 0);

        if(Achou == 0) { printf("\nRegistro inexistente!"); }
        else if(toupper(escolha) == 'N') { printf("\nExclusao cancelada"); }
        else{
            FILE *temp = fopen("temp.dat", "a+b");

            fseek(ArqFarma, 0, 0);
            
            // Copia todos os registros exceto aquele que vai ser deletado
            do {
                fread(&RgFarma, Tamanho, 1, ArqFarma);
                
                if(strcmp(RgFarma.Nome, Farmaco) != 0) { 
                    fwrite(&RgFarma, Tamanho, 1, temp); 
                }
            } while(strcmp(ultimo.Nome, RgFarma.Nome) != 0);
            
            fclose(ArqFarma);
            fclose(temp);

            // Remove o arquivo original
            remove("Farmacos.dat");

            // Substitui o arquivo original, renomeando o arquivo temporario
            rename("temp.dat", "Farmacos.dat");
            ArqFarma = temp;

            printf("\n>>> Exclucao efetuada com sucesso! <<<\n\n");
        }

        ArqFarma = fopen("Farmacos.dat", "a+b");

    } else { printf("Arquivo Vazio.  Nao existem dados a alterar."); }

    printf("\n\n");
    system("pause");
}
	
void Alterar() {
    if(TArquivo(ArqFarma) != 0) {
        TpFarma ultimo = pegaUltimoRegistro(ArqFarma);
        char Farmaco[21], escolha;
        int Achou = 0;

        fclose(ArqFarma); //modo a + b
        ArqFarma = fopen("Farmacos.dat", "r+b");

        system("cls");

        printf("*** alterar ***\n\n"); 

        fseek(ArqFarma, 0, 0);

        printf("Qual farmaco? ");
        scanf("%s", Farmaco);
        
        do {
            fread(&RgFarma, Tamanho, 1, ArqFarma);

            if(strcmp(RgFarma.Nome, Farmaco) == 0) {
                Achou = 1;

                printf("\nNome: %s\n", RgFarma.Nome);
                printf("Valor: R$%.2f\n", RgFarma.Preco);
                printf("Estoque: %d\n", RgFarma.QEstoque);
            }
        } while(strcmp(ultimo.Nome, RgFarma.Nome) != 0 && Achou == 0);

        if (Achou==0) { printf("\nRegistro inexistente!"); }
        else{
            printf("\nQual o novo preco? R$"); 
            scanf("%f", &RgFarma.Preco);

            printf("Qual a nova quantidade? ");
            scanf("%d", &RgFarma.QEstoque);

            fseek(ArqFarma, -Tamanho, 1);
            fwrite(&RgFarma, Tamanho, 1, ArqFarma);

            printf("\n>>> Alteracao efetuada com sucesso! <<<\n\n");
        }

        fclose(ArqFarma);
        ArqFarma = fopen("Farmacos.dat", "a+b");

    } else { printf("Arquivo Vazio.  Nao existem dados a alterar."); }

    system("pause");
}

void Consultar(){
    TpFarma ultimo = pegaUltimoRegistro(ArqFarma);
    char Farmaco[21];
    int Achou = 0;

    system("cls");

    printf("*** consulta ***\n\n");  

    fseek(ArqFarma, 0, 0);

    printf("Qual farmaco? ");
    scanf("%s", Farmaco);
    
    do {
        fread(&RgFarma, Tamanho, 1, ArqFarma);

        if(strcmp(RgFarma.Nome, Farmaco) == 0) {
            Achou = 1;	

            printf("\nNome: %s\n", RgFarma.Nome);
            printf("Valor: R$%.2f\n", RgFarma.Preco);
            printf("Estoque: %d\n", RgFarma.QEstoque);
        }
    } while(strcmp(ultimo.Nome, RgFarma.Nome) != 0 && Achou == 0);

    if(Achou == 0) { printf("\nRegistro inexistente!"); }

    printf("\n");
    system("pause");
}

void LTodos(){
    TpFarma ultimo = pegaUltimoRegistro(ArqFarma);

    system("cls");

    printf("*** lista todos ***\n\n"); 

    if(TArquivo(ArqFarma) == 0) {
        printf("Nao ha registros ainda\n\n");

    } else {
        fseek(ArqFarma, 0, 0);

        do {
            fread(&RgFarma, Tamanho, 1, ArqFarma);
            
            printf("Nome: %s\n", RgFarma.Nome);
            printf("Valor: R$%.2f\n", RgFarma.Preco);
            printf("Estoque: %d\n", RgFarma.QEstoque);
            printf("\n***\n\n");

        } while(strcmp(ultimo.Nome, RgFarma.Nome) != 0);
    }

    system("pause");
}

void escolherArquivo() {
    char nome[21];

    system("cls");

    printf("*** escolher arquivo ***\n\n"); 

    printf("\nQual o nome do arquivo(com .dat): ");
    scanf(" %s", nome);

    if(!arqExiste(nome)) { printf("\nEste arquivo nao existe"); }
    else {
        fclose(ArqFarma);
        ArqFarma = fopen(nome, "a+b");

        printf("\nArquivo trocado com sucesso");
    }

    printf("\n\n");
    system("pause");
}

void apagarArquivo() {
    char nome[21];

    system("cls");

    printf("*** deletar arquivo ***\n\n"); 

    printf("\nQual o nome do arquivo(com .dat): ");
    scanf(" %s", nome);

    if(!arqExiste(nome)) { printf("\nEste ja arquivo nao existe"); }
    else if(strcmp(nome, "Farmacos.dat") == 0) { printf("\nNao e possivel deletar o arquivo principal"); } 
    else if(strcmp(nome, "PaguePouco.c") == 0) { printf("\nNao e possivel deletar o codigo do programa"); }
    else if(strcmp(nome, "PaguePouco.exe") == 0) { printf("\nNao e possivel deletar o executavel do programa"); }
    else {
        char strSeguranca[21];

        printf("\nTodos os dados serao perdidos");
        printf("\nDigite o nome do arquivo novamente para confirmar: ");
        scanf(" %s", strSeguranca);

        if(strcmp(strSeguranca, nome) == 0) {
            remove(nome);

            printf("\nArquivo deletado com sucesso");

        } else { printf("\nProcesso cancelado. Nada foi deletado"); }
    }

    printf("\n\n");
    system("pause");
}

void criarNovoArquivo() {
    FILE* novo;
    char nomeNovo[21];

    system("cls");

    printf("*** criar arquivo ***\n\n"); 

    printf("\nQual o nome do arquivo(com .dat): ");
    scanf(" %s", nomeNovo);

    if(arqExiste(nomeNovo)) { printf("\nEste ja arquivo existe"); }
    else {
        novo = fopen(nomeNovo, "a+b");
        fclose(novo);

        printf("\nArquivo criado com sucesso");
    }

    printf("\n\n");
    system("pause");
}

int main() {
    ArqFarma = fopen("Farmacos.dat", "a+b");

    int Opcao;

    do {
        system("cls");

        printf("\n\n> > > Pague Pouco < < < \n\n");

        printf("Que deseja fazer? \n\n");
        printf("1 - Incluir \n");  
        printf("2 - Excluir \n");
        printf("3 - Alterar \n");
        printf("4 - Consultar \n");
        printf("5 - Listar Todos \n");
        printf("6 - Escolher outro arquivo\n");
        printf("7 - Deletar arquivo por completo\n");
        printf("8 - Criar novo arquivo\n");
        printf("9 - Sair \n\n");

        printf("Opcao: ");
        scanf("%d", &Opcao);

        switch(Opcao) {
            case 1: Incluir(); break; 
            case 2: Excluir(); break; 
            case 3: Alterar(); break; 
            case 4: Consultar(); break; 
            case 5: LTodos(); break;
            case 6: escolherArquivo(); break;
            case 7: apagarArquivo(); break;
            case 8: criarNovoArquivo(); break;
        }
        
    } while(Opcao != 9);

    fclose(ArqFarma);
    
    return 0;
}