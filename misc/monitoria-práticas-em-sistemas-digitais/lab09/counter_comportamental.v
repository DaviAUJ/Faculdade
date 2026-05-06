`timescale 1ns/1ns

module counter_comportamental(
    input wire clk,
    input wire rst,
    output reg [7:0] count
);
    always @(posedge clk or posedge rst) begin
        if(rst) count <= 0;
        else count <= count + 1;
    end 
endmodule;

module tb;
    reg clk;
    reg rst;
    wire [7:0] sla;

    counter_comportamental cc (clk, rst, sla);

    initial begin
        $dumpfile("saida.vcd");
        $dumpvars(0, tb);
        
        rst = 1;
        #5
        rst = 0;
        #5

        clk = 0;
        #10

        clk = 1;
        #10
        
        clk = 0;
        #20

        clk = 1;
        #20

        clk = 0;
        #10

        clk = 1;
        #10

        clk = 0;
        #30

        clk = 1;
        #30

        clk = 0;
        #10

        clk = 1;
        #10

        rst = 1;
        #10

        rst = 0;
        #10
        
        clk = 0;
        #10

        clk = 1;
        #10

        clk = 0; 
        #10

        clk = 1;
        #10

        $finish;
    end
endmodule;
