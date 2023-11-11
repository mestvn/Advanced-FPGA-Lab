`timescale 1ns / 1ps

module top(
    input logic clk, reset,
//    input logic [15:0] ms,
    output logic [3:0] LED,
    
    // slot interface
    input  logic cs, read, write,
    input  logic [4:0] addr,
    input  logic [31:0] wr_data,
    output logic [31:0] rd_data
    );
    
    logic [15:0] reg0, reg1, reg2, reg3;
    logic wr_en;
    
    top_led led0(.ms(reg0), .LED(LED[0]), .*); // 16'h1F40
    top_led led1(.ms(reg1), .LED(LED[1]), .*); // 16'h0FA0
    top_led led2(.ms(reg2), .LED(LED[2]), .*); // 16'h107D0
    top_led led3(.ms(reg3), .LED(LED[3]), .*); // 16'h03E8
    
    always_ff@(posedge clk, posedge reset)
    begin
        if (reset)
        begin
            reg0 = 0;
            reg1 = 0;
            reg2 = 0;
            reg3 = 0;
        end
        else
            if (wr_en)
            begin
                case(addr[1:0])
                    2'b00: reg0 = wr_data[15:0];
                    2'b01: reg1 = wr_data[15:0];
                    2'b10: reg2 = wr_data[15:0];
                    2'b11: reg3 = wr_data[15:0];
                endcase
            end
    end
    
    assign rd_data = 0;
    assign wr_en = cs && write;
endmodule
