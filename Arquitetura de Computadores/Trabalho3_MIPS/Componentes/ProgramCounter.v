module ProgramCounter(input wire clk, rst, input wire [31:0] nextValue, output wire [31:0] value);
    reg [31:0] PC;

    assign value = PC;

    always @(posedge clk) begin
        if(rst) PC <= 0;
        else PC <= nextValue;
    end
endmodule