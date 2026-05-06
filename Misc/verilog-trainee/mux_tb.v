`timescale 1ns/1ns

module mux_tb;
    reg in0;
    reg in1;
    reg select;
    wire [2:0] out;

    muxBehavioural mux_beh (out[0], in0, in1, select);
    muxGate        mux_gat (out[1], in0, in1, select);
    muxRTL         mux_RTL (out[2], in0, in1, select);

    initial begin
        $dumpfile("mux_tb.vcd");
        $dumpvars(0, mux_tb);

        in0 = 0;
        in1 = 0;
        select = 0;

        #5

        select = 1;

        #5

        in0 = 0;
        in1 = 1;
        select = 0;

        #5

        select = 1;

        #5

        in0 = 1;
        in1 = 0;
        select = 0;

        #5

        select = 1;

        #5
        
        in0 = 1;
        in1 = 1;
        select = 0;

        #5

        select = 1;

        #5

        $finish;
    end
endmodule
