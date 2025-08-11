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

        A = 4'b0;
        B = 4'b0;

        for(integer i = 0; i < 16; i = i + 1) begin
            A = i[3:0];

            for(integer j = 0; j < 16; j = j + 1) begin
                B = j[3:0];
                #10;
            end
        end

        $finish;
    end
endmodule