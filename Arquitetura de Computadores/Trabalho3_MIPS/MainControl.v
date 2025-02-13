module MainControl(
    input wire [5:0] opcode,
    output reg regDst,
    output reg jump,
    output reg branch,
    output reg memRead,
    output reg memToReg,
    output reg [1:0] ALUOp,
    output reg memWrite,
    output reg ALUSrc,
    output reg regWrite,
    output reg link
);  
    always @(*) begin
        case(opcode)
            // R-Type
            6'b0: begin
                regDst = 1'b1;
                jump = 1'b0;
                branch = 1'b0;
                memRead = 1'b0;
                memToReg = 1'b0;
                ALUOp = 2'b10;
                memWrite = 1'b0;
                ALUSrc = 1'b0;
                regWrite = 1'b1;
                link = 1'b0;
            end

            // lw
            6'b100011: begin
                regDst = 1'b0;
                jump = 1'b0;
                branch = 1'b0;
                memRead = 1'b1;
                memToReg = 1'b1;
                ALUOp = 2'b0;
                memWrite = 1'b0;
                ALUSrc = 1'b1;
                regWrite = 1'b1;
                link = 1'b0;
            end

            // sw
            6'b101011: begin
                regDst = 1'bX;
                jump = 1'b0;
                branch = 1'b0;
                memRead = 1'b0;
                memToReg = 1'bX;
                ALUOp = 2'b0;
                memWrite = 1'b1;
                ALUSrc = 1'b1;
                regWrite = 1'b0;
                link = 1'b0;
            end

            // beq
            6'b100: begin
                regDst = 1'bX;
                jump = 1'b0;
                branch = 1'b1;
                memRead = 1'b0;
                memToReg = 1'bX;
                ALUOp = 2'b1;
                memWrite = 1'b0;
                ALUSrc = 1'b0;
                regWrite = 1'b0;
                link = 1'b0;
            end

            // addi
            6'b1000: begin
                regDst = 1'b0;
                jump = 1'b0;
                branch = 1'b0;
                memRead = 1'b0;
                memToReg = 1'b0;
                ALUOp = 2'b0;
                memWrite = 1'b0;
                ALUSrc = 1'b1;
                regWrite = 1'b1;
                link = 1'b0;
            end

            // jump
            6'b10: begin
                regDst = 1'bX;
                jump = 1'b1;
                branch = 1'bX;
                memRead = 1'b0;
                memToReg = 1'bX;
                ALUOp = 2'bXX;
                memWrite = 1'b0;
                ALUSrc = 1'bX;
                regWrite = 1'b1;
                link = 1'b0;
            end 

            // jal
            6'b11: begin
                regDst = 1'bX;
                jump = 1'b1;
                branch = 1'b0;
                memRead = 1'bX;
                memToReg = 1'bX;
                ALUOp = 2'bXX;
                memWrite = 1'b0;
                ALUSrc = 1'bX;
                regWrite = 1'b1;
                link = 1'b1;
            end

            default: begin
                regDst = 1'b0;
                jump = 1'b0;
                branch = 1'b0;
                memRead = 1'b0;
                memToReg = 1'b0;
                ALUOp = 2'b0;
                memWrite = 1'b0;
                ALUSrc = 1'b0;
                regWrite = 1'b0;
                link = 1'b0;
            end
        endcase
    end
endmodule