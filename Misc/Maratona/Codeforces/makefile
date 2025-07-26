COMPILER = g++
FLAGS    = -Wall -O3 -lm -pedantic-errors -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -Werror -std=c++20
EXEC     = sla.elf

run:
	$(COMPILER) -o $(EXEC) $(ARGS) $(FLAGS)
	./$(EXEC)
	rm -f $(EXEC)