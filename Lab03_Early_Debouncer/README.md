# Lab 3: Early Detection Debouncing Circuit

DEMO: temp.link
> **NOTE: Didn't get to record circuit wise, so there's a testbench!**

## Part 1: State Diagram & ASM Chart
They should look quite similar, noting that zero and one are asynchronous, and their waiting states are synchronous with the 10ms m_tick.
![State Diagram & ASM Chart](https://github.com/mestvn/Advanced-FPGA-Lab/blob/main/Lab03_Early_Debouncer/early_db.png)

## Part 2: Develop Code
- ticker.sv creates the 10ms m_tick with a counter.
- fsm.sv is based off the state diagram as Moore's - each state has an output.
- early_db.sv is top module with JA outputs

## Part 3: Testbench
Very long testbench is created using T=10_000_000 as 10 million steps (ns) which = 10ms ticks.
> **NOTE: Make sure to set simulation time to 100ms to see full simulation.**
