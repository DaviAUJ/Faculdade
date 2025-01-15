module FullAdder(
    output R, Cout,
    input A, B, Cin
);
    wire a;

    xor xor0 (a, A, B);
    xor xor1 (R, a, Cin);

    wire b, c, d;

    and and0 (b, A, B);
    and and1 (c, A, Cin);
    and and2 (d, B, Cin);
    or or0 (Cout, b, c, d);
endmodule