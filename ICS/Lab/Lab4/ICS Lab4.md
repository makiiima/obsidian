# ICS Lab4

> Yunfan Li
>
> 3200102555

## Introduction
In this lab, we were tasked with implementing a slower version of the game Flappy Bird using LC-3 assembly language. The game involves controlling a bird to fly through a series of obstacles. The bird is represented by three continuous characters that move from top to bottom. The user can control the bird's movement by pressing the corresponding keys on the keyboard. The game ends when the bird flies too high or falls to the ground. The program is divided into three parts: the system booting code, the interrupt service routine, and the user program.

## Algorithm

### System Booting Code
The system booting code initializes the system stack and sets up the interrupt handling for the keyboard. The keyboard interrupt is enabled by setting the interrupt enable bit in the device status register (KBSR) to 1. The starting address of the interrupt service routine is stored in the interrupt vector table at x0180.

### Interrupt Service Routine
The interrupt service routine handles the keyboard input. It waits until a key is pressed, reads the ASCII code of the key, and performs the corresponding action. If the key pressed is a letter, the bird's appearance is changed. If the key pressed is a digit, the bird is moved to the right by the corresponding number of characters. The interrupt service routine uses several registers to store the values of the variables.

```pseudocode
PRESSED:
while(KBSR[15] == 0)
    continue
R0 = KBDR
if(R0 >= 'a' && R0 <= 'z')
    R4 = R0
else if(R0 >= '0' && R0 <= '9')
    R2 = R0 - '0'
    R3 = R3 + R2
    if(R3 > 0x3211)
        R3 = 0x3212
toRTI:
return
```

### User Program
The user program continuously displays the game on the console. The bird is represented by three continuous characters that move from top to bottom. The user can control the bird's movement by pressing the corresponding keys on the keyboard. The bird's appearance changes when a letter key is pressed. The program displays 20 characters per line, and a dot is used to represent the air. The bird's position and appearance are set at the beginning of the program. The program uses a delay subroutine to slow down the game.

```pseudocode
R3 = 0x3211
R4 = 'a'
while(true):
    print 20 dots and a new line
    print R4 3 times
    delay for a short time
    move R3 left by 1
    if(R3 < StrBGN)
        R3 = StrBGN
```

## TA Question

Q: What is the privilege level of keyboard interrupt?

A: It's 4($$100_2$$).