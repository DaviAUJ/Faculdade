IVERILOG = iverilog
VVP = vvp
GTKWAVE = gtkwave
TB = testbench.v
VVPFILE = testbench.vvp
VCD = testbench.vcd

.PHONY: all sim run view clean

all: sim run view clean

sim: $(TB)
		$(IVERILOG) -o $(VVPFILE) $(TB)

run: $(VVPFILE)
		$(VVP) $(VVPFILE)

view: $(VCD)
		$(GTKWAVE) $(VCD)

clean:
		rm -f $(VVPFILE) $(VCD)