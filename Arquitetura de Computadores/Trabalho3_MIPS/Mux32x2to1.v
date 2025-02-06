module Mux32x2to1(
    input wire [31:0] in0, 
    input wire [31:0] in1,
    input wire S, 
    output wire output [31:0] out
);
    assign out = (S) ? in1 : in0;
endmodule