module Registers(
    input [4:0] readReg1, readReg2, writeReg
    input writeEnable,
    input [31:0] writeData,
    output [31:0] readData1, readData2
);
    reg [31:0] registers [31:0];

    integer i;
    initial begin  
        for(i = 0; i < 32; i = i + 1) begin
            registers[i] = 32'b0;
        end
    end

    assign readData1 = registers[readReg1];
    assign readData2 = registers[readReg2];

    always @(*) begin
        if(writeEnable && writeReg != 5'b0) begin
            registers[writeReg] <= writeData;
        end
    end
endmodule