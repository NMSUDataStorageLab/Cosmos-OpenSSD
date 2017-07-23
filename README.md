# Cosmos-OpenSSD
The Cosmos Platform is an open sourced PCIe-based SSD platform based on the HYU Tiger3 controller.

# Requirements
This directory is the working version of Cosmos-OpenSSD GreedyFTL.

The following hardware and software is used to successfully compile the firmware.

Hardware components:
●   Cosmos OpenSSDplatform board
  
●   External PCIeadapter
  
●   External PCIecable
  
●   JTAG cable
  
    – USB type A to USB type micro B cable
  
    – Emulator, JTAG N pin cable (N: 7, 14, 20)
  
●   USB type A to USB type A cable for UART

Software:

●   Windows 10 Pro 64bit
  
●   Xilinx SDK 2014.4
  
●   Xilinx ISE design suite 14.7 system edition
  
●   UART terminal emulator software
  
    – Xilinx Software Development Kit(SDK) includes UART terminal

PCIedevice driver for Linux.

# Changes
Following Changes has been made according to the original code;

●   Debug statements has been added at various locations in different files to track the flow of the code.






