`timescale 1ns / 1ps

module t_ff(
    input logic t, reset,
    output logic q
    );
    
    always_ff @(posedge reset, posedge t)
    begin
        if (reset)
            q <= 0;
        else
            if (t)
                q <= ~q;
            else
                q <= q;
    end
endmodule