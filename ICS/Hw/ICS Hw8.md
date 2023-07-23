# ICS Hw8

> Yunnan Li
>
> 3200102555

### 9.16

The LC-3 can implement eight trap service routines. 

A RTI instruction must be used to return from a TRAP routine to restore saved values. 

A BR instruction won't work because it would not restore the saved values of PC and CC, and would also not pop the return address from the stack. 

Two memory accesses are made during the processing of a TRAP instruction.

### 9.17

Some external mechanism is the only way to start the clock after it is halted. The Halt service routine can never return after bit[15] of the machine control register is cleared because the clock has stopped, which means that instruction processing has stopped.

STI R0, MCR This instruction clears the most significant bit of the machine control register, stopping the clock.

LD R1, SaveR1

It will bring program control back to the program that executed the HALT instruction.