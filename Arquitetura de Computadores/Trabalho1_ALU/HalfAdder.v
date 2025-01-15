module HalfAdder(
    output R, Cout,
    input A, B
);
    xor xor0 (R, A, B);

    and and0 (Cout, A, B);
endmodule
