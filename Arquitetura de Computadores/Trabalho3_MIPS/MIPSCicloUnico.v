`include "InstructionMem.v"
`include "MainControl.v"

module MIPSCicloUnico();
    reg [31:0] PC;

    initial begin
        PC = 32'b0;
    end

    wire [31:0] instruction;

    InstructionMem InstructionMem0 (PC[7:0], instruction);

    MainControl MainControl0 (instruction[31:26], )// tem que escrever mais
    
    

endmodule