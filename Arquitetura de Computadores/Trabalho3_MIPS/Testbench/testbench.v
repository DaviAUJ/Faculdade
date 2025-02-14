//`include "MIPSCicloUnico.v"
`timescale 1ns/1ns

module testbench;
    reg clk;
    reg rst;

    // Guarda o que tem nos registradores para mostrar no GTKWave
    reg [31:0] registers [31:0];
    reg [31:0] memory [255:0];

    integer iterator;

    MIPSCicloUnico processador (clk, rst);

    always #5 clk = ~clk;

    initial begin
        $dumpfile("saida.vcd");
        $dumpvars(0, processador);

        for(iterator = 0; iterator < 256; iterator = iterator + 1) begin
            $dumpvars(1, memory[iterator]);
        end

        for(iterator = 0; iterator < 32; iterator = iterator + 1) begin
            $dumpvars(1, registers[iterator]);
        end

        // inicializa clock
        clk = 0;

        // reset para começar tudo certo
        rst = 1;
        #10

        rst = 0;
        #10

        // Fim da simulação após 200 ciclos de clock, altere o intervalo a baixo para aumentar a quantidade de ciclos
        #2000
        $finish;
    end
    
    // Esse bloco serve para monitorar os registradores e memória no GTKWave
    always @(posedge clk) begin
        for(iterator = 0; iterator < 32; iterator = iterator + 1) begin
            registers[iterator] = testbench.processador.Registers.registers[iterator];
        end

        for(iterator = 0; iterator < 256; iterator = iterator + 1) begin
            memory[iterator] = testbench.processador.DataMemory.memory[iterator];
        end
    end
endmodule