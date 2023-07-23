# ICS Hw7

> Yunfan Li
>
> 3200102555

### 9.2 

Since synchronous I/O does not rely on a ready bit to communicate between the processor and the I/O device, it does not need a ready bit. Instead, the processor can simply wait for the data to become available, based on the timing of the clock signal. This simplifies the design of the I/O device and reduces the overhead of communicating between the processor and the I/O device.

### 9.6 

If `KBSR[15]==0`, then the data in KBDR is already read, the porgram would read the same character again.

### 9.10

Display hardware is output device, can't write DDR. 

### 9.14 

To determine whether to load from the KBDR or from memory location xFE02, you need to know the context in which the Load instruction is being executed. In other words, you need to know what the program is trying to accomplish with the Load instruction.

### 9.26

The second RET wouldn't return to the original location.