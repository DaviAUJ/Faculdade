module InstructionMem(input [7:0] address, output [31:0] instruction);
    reg [31:0] instructions [255:0];

    integer i;
    initial begin
        for(i = 0; i < 256; i = i + 1) begin
            instructions[i] = 32'b0;
        end

        instructions[0] = 32'b1111110;
        instructions[2] = 32'b101;
        instructions[5] = 32'b1111111111;
    end
    
    assign instruction = instructions[address];
endmodule