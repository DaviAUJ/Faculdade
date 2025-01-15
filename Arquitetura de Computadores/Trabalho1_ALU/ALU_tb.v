`include "ALU.V"
`timescale 1ns/100ps

/*
O teste funcionará assim: 
50 pares de números binários serão gerados aleatoriamente,
cada um destes pares passará pelas oitos operações implementadas nesta ALU.
Também será feito 4 testes especiais para testar os casos extremos.
Esses testes garantirão a consistência da ALU,
visto que as entradas A 5e B vão representar seu escopo total e dentro de todas as possibilidades de F.
*/

module ALU_tb;
    reg [31:0] A, B;
    reg [2:0] F;
    wire [31:0] R;

    ALU uut (R, F, A, B);

    integer seed1 = 174;
    integer seed2 = 156;

    initial begin
        $dumpfile("ALU_tb.vcd");
        $dumpvars(0, ALU_tb);

        repeat(50) begin
            A = $urandom(seed1);
            B = $urandom(seed2);

            for(integer i = 0; i < 8; i = i + 1) begin
                F = i;
                #10;
            end
        end

        A = 32'b00000000000000000000000000000000;
        B = 32'b00000000000000000000000000000000;

        for(integer i = 0; i < 8; i = i + 1) begin
            F = i;
            #10;
        end

        A = 32'b11111111111111111111111111111111;
        B = 32'b00000000000000000000000000000000;

        for(integer i = 0; i < 8; i = i + 1) begin
            F = i;
            #10;
        end

        A = 32'b00000000000000000000000000000000;
        B = 32'b11111111111111111111111111111111;

        for(integer i = 0; i < 8; i = i + 1) begin
            F = i;
            #10;
        end

        A = 32'b11111111111111111111111111111111;
        B = 32'b11111111111111111111111111111111;

        for(integer i = 0; i < 8; i = i + 1) begin
            F = i;
            #10;
        end

        $finish;
    end
endmodule
