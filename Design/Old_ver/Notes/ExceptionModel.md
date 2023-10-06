# AArch64 Exception Model

## Privilege & Exception levels

### Privilege Levels

The current privilege level can only change when the processor takes an exception or returns from an exception. 

- EL0 Application
- EL1 Rich OS
- EL2 Hypervisor
- EL3 Firmware/Secure Monitor

The Exception level can only change when:

- Taking an exception 
- Returning from an exception
- Processor reset
- During Debug state
- Exiting from Debug state

Taking an exception -> the EL can increase/stay the same
Cannot move to a lower privilege level by taking an exception.

Returning from an exception -> the EL can decrease/stay the same
Cannot move to a higher pirvilege level by returning from an exception.

### Types of privilege

Two types:
- privilege in the memory system
- privilege from the point of view of accessing processor resources
> Both are affected by the current privileged EL.

#### Memory privilege


