# ICS Hw3 

> 3200102555
> Yunfan Li

### 3.53 

|      | cycle0 | cycle1 | cycle2 | cycle3 | Cycle4 | cycle5 | cycle6 | Cycle7 |
| ---- | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| D2   | 0      | 1      | 1      | 1      | 1      | 0      | 0      | 0      |
| D1   | 0      | 1      | 1      | 0      | 0      | 1      | 1      | 0      |
| D0   | 0      | 1      | 0      | 1      | 0      | 1      | 0      | 1      |

As a decrementing counter.

### 3.61

1. |  S1  |  S0  |  X   |  Z   | S1'  | S0'  |
    | :--: | :--: | :--: | :--: | :--: | :--: |
    |  0   |  0   |  0   |  1   |  0   |  0   |
    |  0   |  0   |  1   |  1   |  0   |  1   |
    |  0   |  1   |  0   |  0   |  1   |  0   |
    |  0   |  1   |  1   |  0   |  0   |  0   |
    |  1   |  0   |  0   |  0   |  0   |  1   |
    |  1   |  0   |  1   |  0   |  1   |  0   |
    |  1   |  1   |  0   |  0   |  0   |  0   |
    |  1   |  1   |  1   |  0   |  0   |  0   |

2. ```mermaid
    flowchart 
     A([1,00])
     B([0,01])
     C([0,10])
     D([0,11])
     A--X=1-->B--X=0-->C--X=1-->C--X=0-->B--X=1-->A
     A--X=0-->A
     D--X=0-->A
     D--X=1-->A
     
    ```

    

###4.1 

- Memory: storing information for processing
- Processing Unit: processing information such as computing
- Input and Output: input and output information
- Control Unit: controling the processing

###4.3

It literally means the counter of the program, which hints that it is the manager of the programs. But in fact, the program counter contains the address of the next instruction of the program(it is like the PC points the instruction), so the instruction pointer may be more insightful.

###4.8 

1. Log~2~256=8 bits
2. log~2~128=7 bits
3. 32-7-8=17 bits
    For the unsigned number, it would be 2^17^
    For the 2's complement number, it would be 2^16^

###4.10

|      | Fetch Instruction | Decode | Evaluate Address | Fetch Data | Execute | Store Result |
| ---- | ----------------- | ------ | ---------------- | ---------- | ------- | ------------ |
| PC   | 0001,0110,1100    |        |                  |            | 1100    |              |
| IR   | 0001,0110,1100    |        |                  |            |         |              |
| MAR  | 0001,0110,1100    |        |                  | 0110       |         |              |
| MDR  | 0001,0110,1100    |        |                  | 0110       |         |              |

