COMPILER = g++
FLAGS    = -Wall -std=c++20
XFLAGS   = -pedantic-errors -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -Werror
EXEC     = sla.elf
ARGS     = FancyFence.cpp

run:
	$(COMPILER) -o $(EXEC) $(ARGS) $(FLAGS)
	./$(EXEC)
	rm -f $(EXEC)
