module Not32Bit(
    output [31:0] R,
    input [31:0] A
);
    generate
        genvar i;

        for(i = 0; i < 32; i = i + 1) begin
            not (R[i], A[i]);
        end
    endgenerate
endmodule