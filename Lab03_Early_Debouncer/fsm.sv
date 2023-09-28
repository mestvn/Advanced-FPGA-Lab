`timescale 1ns / 1ps

module fsm(
        input logic clk, reset, sw,
        output logic db,
        output logic m_tick // output for sim view
    );
    
    ticker tick(
        .clock(clk),
        .reset(reset),
        .tenMS(m_tick)       
        );
    typedef enum {zero, one, wait1_1, wait1_2, wait1_3, wait0_1, wait0_2, wait0_3} state_type;
    
    state_type state_reg, state_next;
    
    always_ff @(posedge clk, posedge reset)
    begin
        if(reset)
            state_reg <= zero;
        else
            state_reg <= state_next;
    end 
    
    always_comb 
    begin
        case(state_reg)
            zero:
            begin
                db = 0;
                if(sw)
                    state_next = wait1_1;
                else
                    state_next = zero;
            end
            wait1_1:
            begin
                db = 1;
                if(m_tick)
                    state_next = wait1_2;
                else
                    state_next = wait1_1;
            end
            wait1_2:
            begin
                db = 1;
                if(m_tick)
                    state_next = wait1_3;
                else
                    state_next = wait1_2;
            end
            wait1_3:
            begin
                db = 1;
                if(m_tick)
                begin
                    if(sw)
                        state_next = one;
                    else
                        state_next = zero;
                end
                else 
                    state_next = wait1_3;
            end
            one:
            begin
                db = 1;
                if(~sw)
                    state_next = wait0_1;
                else
                    state_next = one;
            end
            wait0_1:
            begin
                db = 0;
                if(m_tick)
                    state_next = wait0_2;
                else
                    state_next = wait0_1;
            end
            wait0_2:
            begin
                db = 0;
                if(~m_tick)
                    state_next = wait0_3;
                else 
                    state_next = wait0_2;
            end
            wait0_3:
            begin
                db = 0;
                if(m_tick)
                begin
                    if(~sw)
                        state_next = zero;
                    else
                        state_next = one;
                end
                else
                    state_next = wait0_3;
            end
            default: state_next = zero;
        endcase
    end
endmodule