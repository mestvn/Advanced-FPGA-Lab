`timescale 1ns / 1ps

module bin2dec(
    input logic [7:0] bin,
    output logic [4:0] bcdOnes, bcdTens, bcdHuns
    );
    logic [11:0] bcdTemp;
    logic [3:0] i;

always @(bin)
begin
    bcdTemp = 0; //initialize bcd to zero.
    for (i = 0; i < 8; i = i+1) //run for 8 iterations
    begin
        bcdTemp = {bcdTemp[10:0],bin[7-i]}; //concatenation

    //if a hex digit of 'bcd' is more than 4, add 3 to it.
    if(i < 7 && bcdTemp[3:0] > 4)
        bcdTemp[3:0] = bcdTemp[3:0] + 3;
    if(i < 7 && bcdTemp[7:4] > 4)
        bcdTemp[7:4] = bcdTemp[7:4] + 3;
    if(i < 7 && bcdTemp[11:8] > 4)
        bcdTemp[11:8] = bcdTemp[11:8] + 3;
    end
    bcdOnes <= bcdTemp[3:0];
    bcdTens <= bcdTemp[7:4];
    bcdHuns <= bcdTemp[11:8];
end
endmodule