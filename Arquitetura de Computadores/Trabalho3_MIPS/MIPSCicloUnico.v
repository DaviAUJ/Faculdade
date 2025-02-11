`include "InstructionMem.v"
`include "MainControl.v"
`include "Registers.v"
`include "Mux5x2to1.v"
`include "SignalExtend.v"
`include "ALUControl.v"
`include "Mux32x2to1.v"
`include "ALU.v"
`include "DataMemory.v"
`include "Add4.v"
`include "ShiftLeft2.v"
`include "Adder.v"
`include "ProgramCounter.v"

module MIPSCicloUnico(input wire clk, input wire rst);
    // Todo o datapath daqui para baixo
    // Para a instrução jump vai ter uma seção específica
    wire [31:0] PCValue;
    ProgramCounter PC (clk, rst, muxOut4, PCValue);

    wire [31:0] instruction;
    InstructionMem InstructionMem0 (PCValue, instruction);

    wire regDst, jump, branch, memRead, memToReg, memWrite, ALUSrc, regWrite;
    wire [1:0] ALUOp;
    MainControl MainControl0 (
        instruction[31:26],
        regDst,
        jump,
        branch,
        memRead,
        memToReg,
        ALUOp,
        memWrite,
        ALUSrc,
        regWrite
    );

    wire [4:0] muxOut0;
    Mux5x2to1 Mux0 (instruction[20:16], instruction[15:11], regDst, muxOut0);

    wire [31:0] readData1, readData2;
    Registers Registers0 (
        clk,
        instruction[25:21],
        instruction[20:16],
        muxOut0,
        regWrite,
        muxOut2,
        readData1,
        readData2
    );
    
    wire [31:0] ext;
    SignalExtend SignalExtend0 (instruction[15:0], ext);

    wire [3:0] operation;
    ALUControl ALUControl0 (ALUOp, instruction[5:0], operation);

    wire [31:0] muxOut1;
    Mux32x2to1 Mux1 (readData2, ext, ALUSrc, muxOut1);

    wire [31:0] ALUOut;
    wire zero;
    ALU ALU0 (readData1, muxOut1, operation, ALUOut, zero);

    wire [31:0] memOut;
    DataMemory DataMemory0 (clk, memRead, memWrite, ALUOut, readData2, memOut);

    wire [31:0] muxOut2;
    Mux32x2to1 Mux2 (ALUOut, memOut, memToReg, muxOut2);

    wire [31:0] PCPlus4;
    Add4 Add40 (PCValue, PCPlus4);

    wire [31:0] shiftOut;
    ShiftLeft2 ShiftLeft20 (ext, shiftOut);

    wire [31:0] adderOut;
    Adder Adder0 (shiftOut, PCPlus4, adderOut);

    wire andOut;
    and (andOut, branch, zero);

    wire [31:0] muxOut3;
    Mux32x2to1 Mux3 (PCPlus4, adderOut, andOut, muxOut3);

    // Seção para o jump
    wire [31:0] jumpAdress;
    assign jumpAdress = {PCPlus4[31:28], instruction[25:0], 2'b0};

    wire [31:0] muxOut4;
    Mux32x2to1 Mux4 (muxOut3, jumpAdress, jump, muxOut4);
endmodule