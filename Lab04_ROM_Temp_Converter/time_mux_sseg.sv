`timescale 1ns / 1ps

module time_mux_sseg(
    input logic [5:0] in0,in1,in2,in3,
                      in4,in5,in6,in7,
    input logic clk,
    output logic [6:0] sseg,
    output logic dp,
    output logic [7:0] AN
    );
    
    // to_display[0] is for dp
    // to_display[4:1] is the hex to be decoded
    // to_display[5] is to enable/disable a sseg digit
    logic [5:0] to_display;
    logic [19:0] counter_output;
    logic [2:0] controller_counter;
    assign controller_counter = counter_output[19:17];
    
    binary_counter #(.N(20)) c0(
                    .clk(clk),
                    .reset(1'b0),
                    .en(1'b1),
                    .q(counter_output),
                    .max_tick()
                    );
                    
    mux #(.BITS(6)) mux0(
                    .sel(controller_counter),
                    .mux_out(to_display),
                    .*); //all the ins are captured by .*
                    
    decoder  #(.N(3)) decoder0(
                    .in(controller_counter),
                    .enable(1'b1),
                    .AN(AN));
                    
    hex2sseg ssegdecoder(
                    .hex_in(to_display[4:1]),
                    .enable(to_display[5]),
                    .sseg(sseg));
    // decimal point
    assign dp = to_display[0];
endmodule
