module vga_demo 
   #(parameter CD = 12)    // color depth
   (
    input  logic clk,
    input  logic [13:0] sw,
    // to vga monitor
    output logic hsync, vsync,
    output logic[CD-1:0] rgb
   );

   // logic [CD-1:0] declaration
   logic [10:0] hc, vc;
   logic [CD-1:0] back_rgb, gray_rgb, color_rgb, vga_rgb, out_rgb;
   logic [1:0] size;
   
   // body
   // use switches to set background color
   assign back_rgb = sw[11:0];
   assign size = sw[13:12];
   // instantiate bar generator
   bar_demo bar_unit
      (.x(hc), .y(vc), .out_rgb(out_rgb), .*);
   // instantiate color-to-gray conversion circuit
   rgb2gray c2g_unit  
      (.color_rgb(color_rgb), .gray_rgb(gray_rgb));
   // instantiate video synchronization circuit
   vga_sync_demo #(.CD(CD)) sync_unit
      (.clk(clk), .reset(0), .vga_si_rgb(vga_rgb),
       .hsync(hsync), .vsync(vsync), .rgb(rgb), .hc(hc), .vc(vc));
   
//   assign color_rgb = (bypass_bar) ? back_rgb : bar_rgb;
//   // video source selection mux #0  
//   assign vga_rgb = (bypass_gray) ? color_rgb : gray_rgb;
   assign vga_rgb = out_rgb;
endmodule