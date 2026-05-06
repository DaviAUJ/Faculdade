module muxBehavioural(
    output wire out,
    input  wire in0,
    input  wire in1,
    input  wire select
);
    assign out = (select) ? in1 : in0;
endmodule
