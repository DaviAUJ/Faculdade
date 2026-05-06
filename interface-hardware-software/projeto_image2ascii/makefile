FILE = davinascimento_202300027801_image2ascii.s
INPUT = image2ascii.input
OUTPUT = teste.output
BIN = exec.bin
BASE = base.c
ELF = base.elf

main:
	gcc -Wall $(FILE) -o $(BIN)
	./$(BIN) $(INPUT) $(OUTPUT)
	rm -f $(BIN)

base:
	gcc -Wall $(BASE) -o $(ELF)
	./$(ELF)
	rm -f $(ELF)

baseasm:
	gcc -Wall $(BASE) -o $(ELF)
	objdump --disassemble -M intel $(ELF)
	rm -f $(ELF)

debug:
	gcc -Wall -g $(FILE) -o $(BIN)
	gdb --args $(BIN) $(INPUT) $(OUTPUT)
	rm -f $(BIN)

valf:
	gcc -Wall -ggdb3 $(FILE) -o $(BIN)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BIN) $(INPUT) $(OUTPUT)
	rm -f $(BIN)
