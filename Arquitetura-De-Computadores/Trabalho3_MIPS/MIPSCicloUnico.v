module MIPSCicloUnico(input wire clk, input wire rst);
    // Todo o datapath daqui para baixo
    // Para a instrução jump vai ter uma seção específica
    wire [31:0] PCValue;
    ProgramCounter PC (clk, rst, muxOut7, PCValue);

    wire [31:0] instruction;
    InstructionMem InstructionMem (PCValue, instruction);

    wire regDst, jump, branch, memRead, memToReg, memWrite, ALUSrc, regWrite, link;
    wire [1:0] ALUOp;
    MainControl MainControl (
        instruction[31:26],
        regDst,
        jump,
        branch,
        memRead,
        memToReg,
        ALUOp,
        memWrite,
        ALUSrc,
        regWrite,
        link
    );

    wire [4:0] muxOut0;
    Mux5x2to1 Mux0 (instruction[20:16], instruction[15:11], regDst, muxOut0);

    wire [31:0] readData1, readData2;
    Registers Registers (
        clk,
        rst,
        instruction[25:21],
        instruction[20:16],
        muxOut5,
        regWrite,
        muxOut6,
        readData1,
        readData2
    );
    
    wire [31:0] ext;
    SignalExtend SignalExtend (instruction[15:0], ext);

    wire [3:0] operation;
    wire jrEnable;
    ALUControl ALUControl (ALUOp, instruction[5:0], operation, jrEnable);

    wire [31:0] muxOut1;
    Mux32x2to1 Mux1 (readData2, ext, ALUSrc, muxOut1);

    wire [31:0] ALUOut;
    wire zero;
    ALU ALU (readData1, muxOut1, operation, ALUOut, zero);

    wire [31:0] memOut;
    DataMemory DataMemory (clk, memRead, memWrite, ALUOut, readData2, memOut);

    wire [31:0] muxOut2;
    Mux32x2to1 Mux2 (ALUOut, memOut, memToReg, muxOut2);

    wire [31:0] PCPlus4;
    Add4 Add4 (PCValue, PCPlus4);

    wire [31:0] shiftOut;
    ShiftLeft2 ShiftLeft2 (ext, shiftOut);

    wire [31:0] adderOut;
    Adder Adder (shiftOut, PCPlus4, adderOut);

    wire andOut;
    and (andOut, branch, zero);

    wire [31:0] muxOut3;
    Mux32x2to1 Mux3 (PCPlus4, adderOut, andOut, muxOut3);

    // Seção para o jump
    wire [31:0] jumpAdress;
    assign jumpAdress = {PCPlus4[31:28], instruction[25:0], 2'b0};

    wire [31:0] muxOut4;
    Mux32x2to1 Mux4 (muxOut3, jumpAdress, jump, muxOut4);

    // Seção para jal
    // $31(11111) é o $ra
    wire [4:0] muxOut5;
    Mux5x2to1 Mux5 (muxOut0, 5'b11111, link, muxOut5);
    
    wire [31:0] muxOut6;
    Mux32x2to1 Mux6 (muxOut2, PCPlus4, link, muxOut6);

    // Seção para o jr
    wire [31:0] muxOut7;
    Mux32x2to1 Mux7 (muxOut4, muxOut2, jrEnable, muxOut7);
endmodule