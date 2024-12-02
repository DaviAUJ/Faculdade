module somadorcompleto(a, b, ci, s, co);
    input a, b, ci;
    output s, co;

    assign s = a ^ b ^ ci;
    assign co = a & b | a & ci | b & ci;
endmodule

module somador4Bits(
    input [3:0] numa, numb,
    output [3:0] soma,
    output [0:0] co
);
    wire z;
    wire x;
    wire y;

    somadorcompleto s0 (numa[0], numb[0], 1'b0, soma[0], z);
    somadorcompleto s1 (numa[1], numb[1], z, soma[1], x);
    somadorcompleto s2 (numa[2], numb[2], x, soma[2], y);
    somadorcompleto s3 (numa[3], numb[3], y, soma[3], co);

endmodule