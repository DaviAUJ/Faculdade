`timescale 1ns/100ps

module mux(
    output wire out,
    input wire sel, in1, in2
);
    wire not_sel;
    wire a;
    wire b;

    not (not_sel, sel);

    and (a, in1, not_sel);
    and (b, in2, sel);

    or (out, a, b);
endmodule

module mux_tb;
    reg [2:0] in ;
    wire r;

    mux MUX_A (r, in[2], in[1], in[0]);

    initial begin
        $dumpfile("mux_tb.vcd");
        $dumpvars(0, mux_tb);

        for(integer i = 0; i < 8; i = i + 1) begin
            in = i;
            #10;
        end

        $finish;
    end
endmodule
