`include "FullAdder.v"
`include "HalfAdder.v"

module Adder32Bit(
    output [31:0] R,
    output Cout,
    input [31:0] A, B
);
    wire [31:0] CoutWires;
    assign Cout = CoutWires[31];

    // Deve ter forma menos trabalhosa de fazer isso
    HalfAdder halfAdder0 (R[0], CoutWires[0], A[0], B[0]);
    FullAdder FullAdder1 (R[1], CoutWires[1], A[1], B[1], CoutWires[0]);
    FullAdder FullAdder2 (R[2], CoutWires[2], A[2], B[2], CoutWires[1]);
    FullAdder FullAdder3 (R[3], CoutWires[3], A[3], B[3], CoutWires[2]);
    FullAdder FullAdder4 (R[4], CoutWires[4], A[4], B[4], CoutWires[3]);
    FullAdder FullAdder5 (R[5], CoutWires[5], A[5], B[5], CoutWires[4]);
    FullAdder FullAdder6 (R[6], CoutWires[6], A[6], B[6], CoutWires[5]);
    FullAdder FullAdder7 (R[7], CoutWires[7], A[7], B[7], CoutWires[6]);
    FullAdder FullAdder8 (R[8], CoutWires[8], A[8], B[8], CoutWires[7]);
    FullAdder FullAdder9 (R[9], CoutWires[9], A[9], B[9], CoutWires[8]);
    FullAdder FullAdder10 (R[10], CoutWires[10], A[10], B[10], CoutWires[9]);
    FullAdder FullAdder11 (R[11], CoutWires[11], A[11], B[11], CoutWires[10]);
    FullAdder FullAdder12 (R[12], CoutWires[12], A[12], B[12], CoutWires[11]);
    FullAdder FullAdder13 (R[13], CoutWires[13], A[13], B[13], CoutWires[12]);
    FullAdder FullAdder14 (R[14], CoutWires[14], A[14], B[14], CoutWires[13]);
    FullAdder FullAdder15 (R[15], CoutWires[15], A[15], B[15], CoutWires[14]);
    FullAdder FullAdder16 (R[16], CoutWires[16], A[16], B[16], CoutWires[15]);
    FullAdder FullAdder17 (R[17], CoutWires[17], A[17], B[17], CoutWires[16]);
    FullAdder FullAdder18 (R[18], CoutWires[18], A[18], B[18], CoutWires[17]);
    FullAdder FullAdder19 (R[19], CoutWires[19], A[19], B[19], CoutWires[18]);
    FullAdder FullAdder20 (R[20], CoutWires[20], A[20], B[20], CoutWires[19]);
    FullAdder FullAdder21 (R[21], CoutWires[21], A[21], B[21], CoutWires[20]);
    FullAdder FullAdder22 (R[22], CoutWires[22], A[22], B[22], CoutWires[21]);
    FullAdder FullAdder23 (R[23], CoutWires[23], A[23], B[23], CoutWires[22]);
    FullAdder FullAdder24 (R[24], CoutWires[24], A[24], B[24], CoutWires[23]);
    FullAdder FullAdder25 (R[25], CoutWires[25], A[25], B[25], CoutWires[24]);
    FullAdder FullAdder26 (R[26], CoutWires[26], A[26], B[26], CoutWires[25]);
    FullAdder FullAdder27 (R[27], CoutWires[27], A[27], B[27], CoutWires[26]);
    FullAdder FullAdder28 (R[28], CoutWires[28], A[28], B[28], CoutWires[27]);
    FullAdder FullAdder29 (R[29], CoutWires[29], A[29], B[29], CoutWires[28]);
    FullAdder FullAdder30 (R[30], CoutWires[30], A[30], B[30], CoutWires[29]);
    FullAdder FullAdder31 (R[31], CoutWires[31], A[31], B[31], CoutWires[30]);
endmodule