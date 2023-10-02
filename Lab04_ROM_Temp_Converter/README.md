# Lab 4: ROM-based Temperature Conversion

DEMO: https://youtube.com/shorts/TGaWkNJq7ZI?feature=share
![Block Diagram]https://github.com/mestvn/Advanced-FPGA-Lab/blob/main/Lab04_ROM_Temp_Converter/block_diagram.png

## ROMs:
Two 256 rows of 8-bit .mem lookup tables:
    1) C to F has 0-100 conversions with 101-255 being out of bounds = 0
    2) F to C has 32-212 conversions with 0-31 and 213-255 being out of bounds = 0

## Binary to BCD:
Outsourced code uses the double dabble technique: https://www.electro-tech-online.com/threads/8-bits-binary-number-to-3-digit-display.162468/post-1413119

## 7 segment uses Time-Multiplexing:
This has been done in previous labs, but new code uses revamped professor's example.
