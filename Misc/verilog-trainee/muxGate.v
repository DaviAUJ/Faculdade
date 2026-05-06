module muxGate(
    output wire out,
    input  wire in0,
    input  wire in1,
    input  wire select
);
    wire n_select;
    wire [1:0] and_out;

    not (n_select, select);

    and (and_out[0], in0, n_select),
        (and_out[1], in1, select);

    or  (out, and_out[0], and_out[1]);
endmodule
