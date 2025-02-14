# [windows, linux]
SYS = windows

MAIN = MIPSCicloUnico.v
TB = Testbench/testbench.v
COMPONENTS = $(wildcard Componentes/*.v)

VVP = saida.vvp
VCD = saida.vcd

.PHONY: all compile run analyze clean

all: compile run analyze clean

compile: $(MAIN) $(TB) $(COMPONENTS)
	iverilog -o $(VVP) $^

run: $(VVP)
	vvp $<

analyze: $(VCD)
	gtkwave $<

clean: $(VVP) $(VCD)
ifeq ($(SYS), windows)
	del $^
else
	rm -f $^
endif