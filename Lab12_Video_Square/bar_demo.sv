/*-======================================================================
-- Description: generate a 3-level test bar pattern:
--   * gray scale 
--   * 8 prime colors
--   * a continuous color spectrum
--   * it is customized for 12-bit VGA
--   * two registers form 2-clock delay line  
--======================================================================*/

module bar_demo 
   (
    input  logic [10:0] x, y,     // treated as x-/y-axis
    input logic [1:0] size,
    input logic [11:0] back_rgb,
    output logic [11:0] out_rgb 
   );

   // declaration
   logic [3:0] r, g, b;
   logic [6:0] range;
   
    // square range
    always_comb
    begin
        case(size)
            2'b00: range = 7'b0001000; // 8
            2'b01: range = 7'b0010000; // 16
            2'b10: range = 7'b0100000; // 32
            2'b11: range = 7'b1000000; // 64
        endcase
    end
   
    // color logic
    always_comb
    begin
        if (((x >= 319 - range) && (x <= 319 + range))&&((y >= 239 - range) && (y <= 239 + range)))
        begin
            r = back_rgb[3:0];
            g = back_rgb[7:4];
            b = back_rgb[11:8];
        end
        else
        begin
            r = 4'b1111 - back_rgb[3:0];
            g = 4'b1111 - back_rgb[7:4];
            b = 4'b1111 - back_rgb[11:8];
        end
    end
 
   // output
   assign out_rgb = {r, g, b};
endmodule
