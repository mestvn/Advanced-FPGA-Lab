`timescale 1ns / 1ps

module top_led(
    input logic clk, reset,
    input logic [15:0] ms,
    output logic LED
    );
    
    logic m_tick, toggle;
    mod_counter milli (
            .count(17'h186A0),
            .max_tick(m_tick),
            .*);
    t_ff flipflop(
            .t(toggle),
            .q(LED),
            .*);
    
    logic [15:0] r_next, r_reg;
    always_ff @(posedge clk, posedge reset)
    begin
        if(reset)
            r_next <= 0;
        else
            if (m_tick == 1)
                r_next <= r_reg + 1;
            else if (r_reg == ms)
                r_next <= 0;
            else
                r_next <= r_reg;
    end
    
    assign r_reg = r_next;
    assign toggle = (r_reg == ms) ? 1'b1 : 1'b0;
endmodule
