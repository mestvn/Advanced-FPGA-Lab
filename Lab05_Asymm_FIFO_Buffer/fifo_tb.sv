`timescale 1ns / 1ps

module fifo_tb(
    );
    // signal declarations
    localparam DATA_WIDTH = 8;
    localparam ADDR_WIDTH = 3;
    localparam T = 10; //clock period
    
    logic clk, reset;
    logic wr, rd;
    logic [DATA_WIDTH*2 - 1:0] w_data;
    logic [DATA_WIDTH -1: 0] r_data;
    logic full, empty;
    
    // instantiate module under test
    fifo #(.DATA_WIDTH(DATA_WIDTH), .ADDR_WIDTH(ADDR_WIDTH)) uut (.*);
    
    // 10 ns clock running forever
    always
    begin
        clk = 1'b1;
        #(T / 2);
        clk = 1'b0;
        #(T / 2);
    end
    
    // reset for the first half cylce
    initial
    begin
        reset = 1'b1;
        rd = 1'b0;
        wr = 1'b0;
        @(negedge clk);
        reset = 1'b0;
    end
    
    //test vectors
    initial
    begin
        // ----------------EMPTY-----------------------
        // write
        @(negedge clk);
        w_data = 16'habcd;
        wr = 1'b1;     
        @(negedge clk);
        wr = 1'b0;
        
        // write
        repeat(1) @(negedge clk);
        w_data = 16'h0102;
        wr = 1'b1;
        @(negedge clk)
        wr = 1'b0;
        
        // write
        repeat(1) @(negedge clk);
        w_data = 16'h0304;
        wr = 1'b1;
        @(negedge clk)
        wr = 1'b0;        
        
        // read
        repeat(1) @(negedge clk);
        rd = 1'b1;
        @(negedge clk)
        rd = 1'b0;        
        
        // write
        repeat(1) @(negedge clk);
        w_data = 16'h0506;
        wr = 1'b1;
        @(negedge clk)
        wr = 1'b0;
        
        repeat(1) @(negedge clk);
        rd = 1'b1;
        @(negedge clk)
        rd = 1'b0;        
        
        // write
        repeat(1) @(negedge clk);
        w_data = 16'hdead;
        wr = 1'b1;
        @(negedge clk)
        wr = 1'b0;
        
        repeat(1) @(negedge clk);
        w_data = 16'hfeed;
        wr = 1'b1;
        @(negedge clk)
        wr = 1'b0;
        
        // ----------------FULL-----------------------
        // read until empty
        
        repeat(8)
        begin
            repeat(1) @(negedge clk);
            rd = 1'b1;
            @(negedge clk)
            rd = 1'b0;
        end
        
        // ----------------EMPTY-----------------------
        
        // read & write at the same time
        repeat(1) @(negedge clk);
        w_data = 16'hdcba;
        wr = 1'b1;
        rd = 1'b1;
        @(negedge clk)
        wr = 1'b0;
        rd = 1'b0;
        
        // read again
        repeat(1) @(negedge clk);
        rd = 1'b1;
        @(negedge clk)
        rd = 1'b0;
    
        // read while empty
        repeat(1) @(negedge clk);
        rd = 1'b1;
        @(negedge clk)
        rd = 1'b0;

        // ----------------NOT EMPTY-----------------------
        repeat(1) @(negedge clk);
        w_data = 16'h0110;
        wr = 1'b1;
        @(negedge clk)
        wr = 1'b0;
        
        repeat(1) @(negedge clk);
        w_data = 16'h2332;
        wr = 1'b1;
        @(negedge clk)
        wr = 1'b0;
        
        repeat(1) @(negedge clk);
        w_data = 16'h1234;
        wr = 1'b1;
        @(negedge clk)
        wr = 1'b0;
        
        // read & write at the same time
        repeat(1) @(negedge clk);
        w_data = 16'hdeaf;
        wr = 1'b1;
        rd = 1'b1;
        @(negedge clk)
        wr = 1'b0;
        rd = 1'b0;
        
        repeat(3) @(negedge clk);
        
        // read 8x
        
        repeat(8)
        begin
            repeat(1) @(negedge clk);
            rd = 1'b1;
            @(negedge clk)
            rd = 1'b0;
        end
        $stop;
    end
endmodule
