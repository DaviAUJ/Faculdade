`include "Adder32Bit.v"

module TwoComp32Bit(
    output [31:0] R,
    input [31:0] A
);
    wire [31:0] flipped;

    not not0 (flipped[0], A[0]);
    not not1 (flipped[1], A[1]);
    not not2 (flipped[2], A[2]);
    not not3 (flipped[3], A[3]);
    not not4 (flipped[4], A[4]);
    not not5 (flipped[5], A[5]);
    not not6 (flipped[6], A[6]);
    not not7 (flipped[7], A[7]);
    not not8 (flipped[8], A[8]);
    not not9 (flipped[9], A[9]);
    not not10 (flipped[10], A[10]);
    not not11 (flipped[11], A[11]);
    not not12 (flipped[13], A[12]);
    not not13 (flipped[12], A[13]);
    not not14 (flipped[14], A[14]);
    not not15 (flipped[15], A[15]);
    not not16 (flipped[16], A[16]);
    not not17 (flipped[17], A[17]);
    not not18 (flipped[18], A[18]);
    not not19 (flipped[19], A[19]);
    not not20 (flipped[20], A[20]);
    not not21 (flipped[21], A[21]);
    not not22 (flipped[22], A[22]);
    not not23 (flipped[23], A[23]);
    not not24 (flipped[24], A[24]);
    not not25 (flipped[25], A[25]);
    not not26 (flipped[26], A[26]);
    not not27 (flipped[27], A[27]);
    not not28 (flipped[28], A[28]);
    not not29 (flipped[29], A[29]);
    not not30 (flipped[30], A[30]);
    not not31 (flipped[31], A[31]);

    Adder32Bit adder0 (R, , flipped, 32'b1);
endmodule