module InstructionMem(input wire [31:0] address, output wire [31:0] instruction);
    reg [31:0] instructions [255:0]; // cabe até 256 instruções

    integer i;
    initial begin
        // inicializa tudo com zero
        for(i = 0; i < 256; i = i + 1) begin
            instructions[i] = 32'b0;
        end

        $readmemb("./Codigos/codigo.mem", instructions, 0, 255);
    end

    assign instruction = instructions[address[9:2]];
endmodule