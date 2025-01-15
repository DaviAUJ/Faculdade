`include "Adder32Bit.v"
`include "not32Bit.v"

module TwoComp32Bit(
    output [31:0] R,
    input [31:0] A
);
    wire [31:0] flipped;

    Not32Bit not32Bit (flipped, A);
    Adder32Bit adder (R, , flipped, 32'b1);
endmodule