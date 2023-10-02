`timescale 1ns / 1ps

module bin2dec_tb();

logic [7:0] bin;
logic [3:0] bcdOnes, bcdTens, bcdHuns;
bin2dec uut(.*);

initial begin
    bin = 8'b00000000; #10; // 0
    bin = 8'b11010100; #10; // 212
    bin = 8'b10011000; #10; // 153
    bin = 8'b10010101; #10; // 149
    bin = 8'b01000101; #10; // 67
    bin = 8'b01101011; #10;
end
endmodule

