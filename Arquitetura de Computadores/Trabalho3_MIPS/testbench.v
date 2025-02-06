`include "ALUControl.v"
`timescale 1ns/100ps

module testbench;
    reg [1:0] A;
    reg [5:0] B;
    wire [3:0] Z;

    ALUControl test (A, B, Z);

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0, testbench);


        A = 2'b0;
        B = 6'bXX0000;
        #1

        B = 6'bXX0010;

        #1

        A = 2'b1;
        B = 6'bXX0000;
        #1

        B = 6'bXX0010;

        #1

        A =2'b10;
        B = 6'bXX0000;
        #1

        B = 6'bXX0010;

        #1

        B = 6'bXX0100;

        #1

        B = 6'bXX0101;

        #1

        B = 6'bXX1010;

        #1

        $finish;
    end
endmodule