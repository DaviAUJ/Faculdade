`include "Somador4Bits.v"
`timescale 1ns/100ps

module somador4Bits_tb;
    reg [3:0] A, B;
    wire [3:0] C;
    wire CARRY_OUT;

    somador4Bits uut (A, B, C, CARRY_OUT);

    initial begin
        $dumpfile("Somador4Bits.vcd");
        $dumpvars(0, somador4Bits_tb);

        repeat(100) begin
            #10;
            A = $urandom_range(15, 0);
            B = $urandom_range(15, 0);
        end

        #10;
        $finish;
    end
endmodule