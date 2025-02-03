InstructionMem(input [7:0] address, output [31:0] instruction);
    reg [31:0] instructions [255:0];
    
    assign instruction = instructions[address];