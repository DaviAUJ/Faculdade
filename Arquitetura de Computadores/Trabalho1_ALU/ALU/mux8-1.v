module mux8-1(
    input [2:0] F,
    input I0, I1, I2, I3, I4, I5, I6, I7
    output R
);
    wire [2:0] FFlipped;
    wire [7:0] T;

    not (FFlipped[0], F[0]),
        (FFlipped[1], F[1]),
        (FFlipped[2], F[2]);

    and (T[0], I0, F[0], F[1], F[2]),
        (T[1], I1, F[0], F[1], FFlipped[2]),
        (T[2], I2, F[0], FFlipped[1], F[2]),
        (T[3], I3, F[0], FFlipped[1], FFlipped[2]),
        (T[4], I4, FFlipped[0], F[1], F[2]),
        (T[5], I5, FFlipped[0], F[1], FFlipped[2]),
        (T[6], I6, FFlipped[0], FFlipped[1], F[2]),
        (T[7], I7, FFlipped[0], FFlipped[1], FFlipped[2]);
        

endmodule