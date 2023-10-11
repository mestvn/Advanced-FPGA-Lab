# Lab 5: Asymmetric FIFO Buffer

DEMO: No demo - just TestBench with 8 bit output and 8 rows for the memory
![TestBench](https://github.com/mestvn/Advanced-FPGA-Lab/blob/main/Lab05_Asymm_FIFO_Buffer/lab5_tb.png)

## First In:
The Write Data is 2x the size of Read Data. Store first half of Write Data in first memory address and second half of Write Data in next memory address. Full flag is raised if there is not 2 memory addresses to write into or the writing pointer matches the read pointer during a write command.

## First Out:
Read Data is done sequentially. Empty flag is raised if the read pointer matches the writing pointer during a read command (values read during an empty flag are also neglectable). Full flag also stays raised until read is executed twice to make room for 2 bytes of data.
