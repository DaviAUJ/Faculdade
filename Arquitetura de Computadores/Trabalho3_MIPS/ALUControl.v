module ALUControl(input wire [1:0] ALUOp, input wire [5:0] instruction, output reg [3:0] operation);
    always @(*) begin
        case(ALUOp)
            2'b0: operation = 4'b10; // +

            2'b1: operation = 4'b110; // -

            2'b10: begin
                case(instruction[3:0]) 
                    4'b0: operation = 4'b10; // +
                    4'b10: operation = 4'b110; // -
                    4'b100: operation = 4'b0; // AND
                    4'b101: operation = 4'b1; // OR
                    4'b1010: operation = 4'b111; // SLT

                    default: operation = 4'b0;
                endcase
            end

            default: operation = 4'b0;
        endcase
    end
endmodule