SHELL = /bin/bash

INPUT = pwcracker.input
OUTPUT = teste.output
SRC = davinascimento_202300027801_pwcracker.c
EXE = exe.elf

run:
	gcc -Wall -o3 $(SRC) -o $(EXE) -lm -lpthread 2>&1
	time ./$(EXE) $(INPUT) $(OUTPUT)
	rm -f $(EXE)

debug:
	gcc -Wall -g $(SRC) -o $(EXE) -lm
	gdb --args $(EXE) $(INPUT) $(OUTPUT)
	rm -f $(EXE)

valf:
	gcc -Wall -ggdb3 -lm $(SRC) -o $(EXE)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXE) $(INPUT) $(OUTPUT)
	rm -f $(EXE)
