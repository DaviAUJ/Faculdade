#!/usr/bin/bash

list=$(ls *.v)

iverilog -o mux_tb.vvp "$list"
vvp mux_tb.vvp
gtkwave mux_tb.vcd
rm mux_tb.vvp mux_tb.vcd
