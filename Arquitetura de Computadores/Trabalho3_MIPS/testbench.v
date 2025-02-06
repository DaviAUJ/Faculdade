`include "SignalExtend.v"
`timescale 1ns/100ps

module testbench;
    reg [15:0] A;
    wire [31:0] Z;

    SignalExtend test (A, Z);

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0, testbench);

        A = 16'b0;

        #1

        A = 16'b1;

        #1

        A = 16'b111;

        #1

        A = 16'b11111011;

        #1

        A = 16'b1101101100111001;

        #1

        $finish;
    end
endmodule