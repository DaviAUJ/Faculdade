`include "Adder32Bit.v"

module TwoComp32Bit(
    output [31:0] R,
    input [31:0] A
);
    wire [31:0] flipped;

    not not0 (flipped, A);
    Adder32Bit adder0 (R, , flipped, 32'b1);
endmodule