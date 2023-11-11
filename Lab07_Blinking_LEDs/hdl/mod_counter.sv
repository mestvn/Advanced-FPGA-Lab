`timescale 1ns / 1ps

module mod_counter
    #(parameter N = 17)
    (
        input logic clk, reset,
        input logic [N-1:0] count,
        output logic max_tick
    );
    
    // signal declaration
    logic [N - 1:0] q, r_next, r_reg;
    
    // body
    // [1] Register segment
    always_ff @(posedge clk, posedge reset)
    begin
        if(reset)
            r_reg <= 0;
        else
            r_reg <= r_next;
    end
    
    // [2] next-state logic segment
    assign r_next = (r_reg == count)? 0: r_reg + 1;
    assign max_tick = (r_reg == count) ? 1'b1: 1'b0;
    
endmodule