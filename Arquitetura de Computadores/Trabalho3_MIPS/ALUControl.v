module ALUControl(input wire [1:0] ALUOp, input wire [5:0] instruction, output wire [3:0] operation);
    case(ALUOp)
        2'b0: assign operation = 4'b10;

        2'b1: assign operation = 4'b110;

        2'b10: begin
            case(instruction[3:0]) 
                4'b0: assign operation = 4'b10;
                4'b10: assign operation = 4'110;
                4'b100: assign operation = 4'b0;
                4'b101: assign operation = 4'b1;
                4'b1010: assign operation = 4'b111;
            endcase
        end
    endcase
endmodule