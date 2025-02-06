module Mux5x2to1(
    input wire [4:0] in0, 
    input wire [4:0] in1,
    input wire S, 
    output wire output [4:0] out
);
    assign out = (S) ? in1 : in0;
endmodule