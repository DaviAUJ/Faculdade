`include "MIPSCicloUnico.v"
`timescale 1ns/1ns

module testbench;
    reg clk;
    reg rst;

    // Guarda o que tem nos registradores para mostrar no GTKWave
    reg [31:0] registers [31:0];

    integer iterator;
    integer iterator2;

    MIPSCicloUnico test (clk, rst);

    always #5 clk = ~clk;

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0, testbench);

        // Este for junto do bloco always abaixo serve para monitorar os registradores lá no GTKWave
        for(iterator2 = 0; iterator2 < 32; iterator2 = iterator2 + 1) begin
            $dumpvars(1, registers[iterator2]);
        end

        // inicializa clock
        clk = 0;

        // reset para começar tudo certo
        rst = 1;
        #10

        rst = 0;
        #10

        // Fim da simulação após 100 ciclos de clock, altere o intervalo a baixo para aumentar a quantidade de ciclos
        #1000
        $finish;
    end
    
    always @(posedge clk) begin
        for (iterator = 0; iterator < 32; iterator = iterator + 1) begin
            registers[iterator] = testbench.test.Registers0.registers[iterator];
        end
    end
endmodule