module MainControl(
    input wire [5:0] opcode,
    output wire regDst,
    output wire branch,
    output wire memRead,
    output wire memToReg,
    output wire [1:0] ALUOp,
    output wire memWrite,
    output wire ALUSrc,
    output wire regWrite
);
    case(opcode)
        6'b0: begin
            assign regDst = 1'b1;
            assign branch = 1'b0;
            assign memRead = 1'b0;
            assign memToReg = 1'b0;
            assign ALUOp = 2'b10;
            assign memWrite = 1'b0;
            assign ALUSrc = 1'b0;
            assign regWrite = 1'b1;
        end
        6'b100011: begin
            assign regDst = 1'b0;
            assign branch = 1'b0;
            assign memRead = 1'b1;
            assign memToReg = 1'b1;
            assign ALUOp = 2'b0;
            assign memWrite = 1'b0;
            assign ALUSrc = 1'b1;
            assign regWrite = 1'b1;
        end
        6'b101011: begin
            assign regDst = 1'bX;
            assign branch = 1'b0;
            assign memRead = 1'b0;
            assign memToReg = 1'bX;
            assign ALUOp = 2'b0;
            assign memWrite = 1'b1;
            assign ALUSrc = 1'b1;
            assign regWrite = 1'b0;
        end
        6'b100: begin
            assign regDst = 1'bX;
            assign branch = 1'b1;
            assign memRead = 1'b0;
            assign memToReg = 1'bX;
            assign ALUOp = 2'b1;
            assign memWrite = 1'b0;
            assign ALUSrc = 1'b0;
            assign regWrite = 1'b0;
        end
    endcase
endmodule