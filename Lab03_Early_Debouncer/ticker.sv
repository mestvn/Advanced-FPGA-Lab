`timescale 1ns / 1ps

module ticker #(parameter N=20)(
    input logic clock, reset,
    output logic tenMS
);
logic [N-1:0] r_reg, r_next;

always_ff @(posedge clock, posedge reset)
begin
    if(reset)
        r_reg <= 0;
    else
        r_reg <= r_next;
end

assign r_next = (r_reg == 1_000_000) ? 0 : r_reg + 1;
assign tenMS = (r_reg == 1_000_000) ? 1'b1 : 1'b0;
 
endmodule

