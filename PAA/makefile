# Variaveis
 # [windows, linux]
SYS = windows
COMPILADOR = gcc

NOME = davinascimento
MATRICULA = 202300027801
PROJETO = quicksort
EXTENSAO = .c

# Deixe vazia se o make estiver no mesmo diretório
PASTA = ./projeto_$(PROJETO)/

EXE = executavel
ENTRADA = $(PASTA)$(PROJETO)
SAIDA = $(PASTA)teste
COMPARAR = $(PASTA)$(PROJETO)

# Nome completo do código-fonte
CODIGO = $(PASTA)$(NOME)_$(MATRICULA)_$(PROJETO)$(EXTENSAO)

.PHONY: all compile run clean diff

all: compile run clean diff

compile: $(CODIGO)
	$(COMPILADOR) -Wall $(CODIGO) -o $(EXE).exe

run: $(EXE).exe
	$(EXE).exe $(ENTRADA).input $(SAIDA).output

clean:
ifeq ($(SYS), windows)
	del $(EXE).exe
else
	rm -f $(EXE).exe
endif

# Compara o resultado esperado no vscode
diff: 
	code -d $(SAIDA).output $(COMPARAR).output