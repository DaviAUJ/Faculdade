module muxRTL(
    output wire out,
    input  wire in0,
    input  wire in1,
    input  wire select
);
    assign out = (in0 & ~select) | (in1 & select);
endmodule
