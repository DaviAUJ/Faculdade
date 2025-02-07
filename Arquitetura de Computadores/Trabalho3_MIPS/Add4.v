module Add4(input wire [31:0] number, output wire [31:0] out);
    assign out = number + 32'b100;
endmodule