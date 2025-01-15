`include "Mux8to1.v"

module Mux32x8to1(
    output [31:0] R,
    input [2:0] F,
    input [31:0] I7, I6, I5, I4, I3, I2, I1, I0
);
    generate
        genvar i;

        for(i = 0; i < 32; i = i + 1) begin
            Mux8to1 mux (R[i], F, I7[i], I6[i], I5[i], I4[i], I3[i], I2[i], I1[i], I0[i]);
        end
    endgenerate
endmodule