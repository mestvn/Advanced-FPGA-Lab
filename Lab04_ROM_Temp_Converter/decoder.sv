`timescale 1ns / 1ps

module decoder #(parameter N = 3)(
    input logic [N - 1:0] in,
    input logic enable,
    output logic [2**N - 1:0] AN
    );
    
    always_comb
    begin
        AN = {2**N{1'b1}}; 
        
        if(enable)
        begin
            integer i;
            for(i = 0; i < 2**N; i = i+1)
            begin
                if (in == i)
                    AN[i] = 1'b0;
            end
        end
    end
endmodule