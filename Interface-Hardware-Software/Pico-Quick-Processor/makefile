SHELL = /bin/zsh

run:
	gcc davinascimento_202300027801_pqp.c -o sla.elf -O3
	time ./sla.elf pqp.input teste.output
	rm sla.elf

debug:
	gcc davinascimento_202300027801_pqp.c -o sla.elf -g
	gdb --args sla.elf pqp.input teste.output
	rm sla.elf

asm:
	gcc davinascimento_202300027801_pqp.c -o sla.elf -O3
	objdump -M intel -D sla.elf
	rm sla.elf

val:
	gcc -o val.elf davinascimento_202300027801_pqp.c -g -O3
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./val.elf pqp.input teste.output
	rm val.elf
