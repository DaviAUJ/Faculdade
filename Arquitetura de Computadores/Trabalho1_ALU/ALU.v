`include "TwoComp32Bit.v"
`include "And32Bit.v"
`include "Or32Bit.v"
`include "Xnor32Bit.v"
`include "Mux32x8to1.v"

module ALU(
    output [31:0] R,
    input [2: 0] F,
    input [31:0] A, B
);
    wire [31:0] Ra, Rb, Rb2, Rc, Rd, Re, Rf, Rg, Rh;
    
    // 000
    Adder32Bit adder (Ra, , A, B);

    // 001
    TwoComp32Bit twoComp (Rb, B);
    Adder32Bit subtr (Rb2, , A, Rb);

    //010
    And32Bit and32 (Rc, A, B);

    //011
    Or32Bit or32 (Rd, A, B);

    //100
    Xnor32Bit xnor32 (Re, A, B);

    //101
    Not32Bit not32a (Rf, A);

    //110
    assign Rg = A;

    //111
    Not32Bit not32b (Rh, B);

    Mux32x8to1 mux (R, F, Ra, Rb2, Rc, Rd, Re, Rf, Rg, Rh);
endmodule