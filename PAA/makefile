# Variaveis
# [windows, linux]
SYS = linux
COMPILADOR = gcc

NOME = davinascimento
MATRICULA = 202300027801
PROJETO = compressao
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


# Comandos principais
main: compile run clean

diff: 
	code -d $(SAIDA).output $(COMPARAR).output

val: compiledb runvalgrind clean

valf: compiledb fastrunvalgrind clean



compile: $(CODIGO)
	$(COMPILADOR) $(CODIGO) -o $(EXE) -Wall -lm

run: $(EXE) $(ENTRADA).input
ifeq ($(SYS), windows)
	$(EXE).exe $(ENTRADA).input $(SAIDA).output
else
	time -p ./$(EXE) $(ENTRADA).input $(SAIDA).output
endif

clean:
ifeq ($(SYS), windows)
	del $(EXE).exe
else
	rm -f $(EXE)
endif

compiledb: $(CODIGO)
	$(COMPILADOR) $(CODIGO) -o $(EXE) -ggdb3 -Wall -lm

runvalgrind: $(EXE)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXE) $(ENTRADA).input $(SAIDA).output

fastrunvalgrind: $(EXE)
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXE) $(ENTRADA).input $(SAIDA).output