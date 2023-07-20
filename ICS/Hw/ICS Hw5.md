# ICS Hw5

> Yunfan Li
>
> 3200102555

### 5.37 change LDI to STI

Memory, MDR, MAR, IR, PC, Reg File, ADDR2MUX, ADDR1MUX set to PC, alongwith the ADDER they connect to, and MAXMUX and GateMARMUX implement the STI instruction, alongwith NZP and the logic which goes with it

### 5.39

IR, PC, Reg File, the SEXT unit connected to IR[8:0], ADDR2MUX, ADDR1MUX set to PC, alongwith the ADDER they connect to, and MAXMUX and GateMARMUX implement the LEA instruction, alongwith NZP and the logic which goes with it.

### 6.24

0110000001000001

### 7.32

| Symbol | Address |
| ------ | ------- |
| SKIP   | x8009   |
| A      | x800A   |
| B      | x8011   |
| BANNER | x8012   |
| C      | x801F   |

x8006: 0010001000000011

x8007: 0000010000000001

x8008:0011000000001000



Line 7 will store the value to B during the program execution;

Line 10 stores the value to B before it's executed

### 7.34

NOT R2, R0

ADD R2, R2, #1

BRz DONE

ADD R0,R0,#1