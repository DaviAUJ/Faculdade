module Xnor32Bit(
    output [31:0] R,
    input [31:0] A, B
);
    generate
        genvar i;

        for(i = 0; i < 32; i = i + 1) begin
            xnor (R[i], A[i], B[i]);
        end
    endgenerate
endmodule