`timescale 1ns / 1ps

module early_db_tb();

logic clk, reset, sw, db, m_tick;
localparam T = 10_000_000;
fsm uut(.*);

// 10 ns clock
always
begin
    clk = 1'b1;
    #5;
    clk = 1'b0;
    #5;
end

// reset
initial begin
    reset = 1'b1;
    #5;
    reset = 1'b0;
end

initial begin
    // bouncing on
    sw = 0; #T;
    sw = 1; #(T/2);
    sw = 0; #(T);
    sw = 1; #(T/4);
    sw = 0; #(T/4);
    sw = 1; #(T/4);
    sw = 0; #(T/8);
    sw = 1; #(T/8);
    
    // bouncing off
    sw = 0; #(T/4);
    sw = 1; #(T/4);
    sw = 0; #(T/2);
    sw = 1; #(T/8);
    sw = 0; #(T*2);
    sw = 1; #(T*3);
    $stop;
end
endmodule
