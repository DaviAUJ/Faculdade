module Mux8to1(
    output R, 
    input [2:0] F,
    input I7, I6, I5, I4, I3, I2, I1, I0
);
    wire [2:0] FFlipped;
    wire [7:0] K;

    not (FFlipped[0], F[0]),
        (FFlipped[1], F[1]),
        (FFlipped[2], F[2]);

    and (K[0], I0, F[2], F[1], F[0]),
        (K[1], I1, F[2], F[1], FFlipped[0]),
        (K[2], I2, F[2], FFlipped[1], F[0]),
        (K[3], I3, F[2], FFlipped[1], FFlipped[0]),
        (K[4], I4, FFlipped[2], F[1], F[0]),
        (K[5], I5, FFlipped[2], F[1], FFlipped[0]),
        (K[6], I6, FFlipped[2], FFlipped[1], F[0]),
        (K[7], I7, FFlipped[2], FFlipped[1], FFlipped[0]);

    or (R, K[0], K[1], K[2], K[3], K[4], K[5], K[6], K[7]);
endmodule