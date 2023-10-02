`timescale 1ns / 1ps

module bram
    #(parameter memFile = "C2F_LUT.mem")(
    input logic clk,
    input logic [7:0] addr,
    output logic [7:0] data
    );
    
    (*rom_style = "block" *)logic [7:0] rom [0:255];
    initial
    begin
        $readmemb(memFile,rom);
    end
        
    always_ff @ (posedge clk)
    begin
        data <= rom[addr];
    end
endmodule
