`timescale 1ns / 1ps

module early_db(
        input logic clk, reset, sw,
        output logic db, m_tick,
        output logic [2:1] JA
    );
    
    fsm debouncer(.*);
    
    assign JA[1] = sw;
    assign JA[2] = db;
endmodule
