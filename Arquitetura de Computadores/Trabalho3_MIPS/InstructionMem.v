module InstructionMem(input [7:0] address, output [31:0] instruction);
    reg [31:0] instructions [1023:0];

    integer i;
    initial begin
        for(i = 0; i < 1024; i = i + 1) begin
            instructions[i] = 32'b0;
        end
    end
    
    assign instruction = instructions[address];
endmodule