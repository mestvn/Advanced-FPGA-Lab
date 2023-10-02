`timescale 1ns / 1ps

module top(
    input logic clk, cf,
    input logic [7:0] SW,
    output logic [6:0] sseg,
    output logic dp,
    output logic [7:0] AN
    );
    
    logic [7:0] c2f, f2c, conv;
    logic [3:0] ones0, tens0, huns0,
                ones1, tens1, huns1,
                temp_char, conv_char;
    
    bram #(.memFile("C2F_LUT.mem")) convF(
        .addr(SW),
        .data(c2f),
        .*
        );
    bram #(.memFile("F2C_LUT.mem")) convC(
        .addr(SW),
        .data(f2c),
        .*
        );    
    bin2dec sw2bcd(
    .bin(SW),
    .bcdOnes(ones0),
    .bcdTens(tens0),
    .bcdHuns(huns0)
    );
    bin2dec conv2bcd(
    .bin(conv),
    .bcdOnes(ones1),
    .bcdTens(tens1),
    .bcdHuns(huns1)
    );
    
    time_mux_sseg seg(
        .in0({1'b1,ones1,1'b1}),
        .in1({1'b1,tens1,1'b1}),
        .in2({1'b1,huns1,1'b1}),
        .in3({1'b1,conv_char,1'b1}),
        .in4({1'b1,ones0,1'b1}),
        .in5({1'b1,tens0,1'b1}),
        .in6({1'b1,huns0,1'b1}),
        .in7({1'b1,temp_char,1'b1}),
        .*
        );
        
    assign conv = cf ? f2c : c2f;
    assign temp_char = cf ? 4'hF : 4'hC;
    assign conv_char = cf ? 4'hC : 4'hF;
endmodule
