`include "TwoComp32Bit.v"
`timescale 1ns/100ps

module teste;
    reg [31:0] A;
    wire [31:0] R;
    wire Cout;

    TwoComp32Bit uut (R, A);

    initial begin
        $dumpfile("TwoComp32Bit.vcd");
        $dumpvars(0, teste);

       A = 32'b10;
       #10
       A = 32'b11111111111111111111111111111111;
       #10

       $finish;
    end
endmodule