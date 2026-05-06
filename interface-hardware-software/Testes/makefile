FILE = CLink.s
OBJECT = obj.o
EXE = exec
ENTRY_POINT = Main

main: assemble link run clean

assemble: $(FILE)
	nasm -f elf64 -o $(OBJECT) $(FILE)

link: $(OBJECT)
	gcc -z noexecstack -no-pie $(OBJECT) -o $(EXE)

run: $(EXE)
	./$(EXE)

clean:
	rm -f ./$(EXE) ./$(OBJECT)
