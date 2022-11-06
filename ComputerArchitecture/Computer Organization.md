# Chap.4 The Processor

## 4.1 Introduction

### A Basic RISC-V Implementation
- memory access instruction `ld`, `sd`
- 算数指令`add, sub, and, or`
- conditional branch instruction *branch if equal* `beq`

### An overview of implementation
执行以上指令的大部分工作相同
1. 程序计数器`PC`发送到指令所在的存储单元，并取出指令
2. 根据指令的某些字段选择需要读取的一个/两个寄存器
3. 剩余操作取决于指令类别

## 4.2 Logic Design Conventions

两种不同的逻辑单元
- 组合逻辑：处理数据值的单元
- 状态单元(*sequential*)：有内部存储功能，包含状态
    - 一个状态单元至少有
    - 两个输入：
        - 写入状态单元的数据值
        - 决定何时写入的时钟信号
    - 一个输出：
        - 在前一个时钟周期写入单元的数据值
    - 何时被写入由时钟确定，但是可以随时被读

### Clocking Methodology

时钟同步方法规定了信号可以读出和写入的时间

我们采用边沿触发的时钟（edge-triggered clocking），即仅在时钟边沿更新；如果状态单元在每个有效的时钟边沿都进行写入，则可忽略写控制信号，反之则需要；仅当时钟边沿到来且写控制信号有效时，状态单元改变状态

![image-20221103032823267](image-20221103032823267.png)

## 4.3 Building a Datapath

### R-type

- 读取两个寄存器，对他们的内容执行ALU操作，再将结果写回寄存器
- 被称为R型指令或者算数逻辑指令（*arithmetic-logical instructions*）

为写入一个数据字，需要
- 指定要写的寄存器号
- 要写入寄存器的数据
总共需要四个输入,未标注的为64位宽
![[Pasted image 20221105101854.png]]
### 存取指令

不仅需要寄存器堆和ALU，还需要单元将指令中的12位偏移量符号拓展为64位
![[Pasted image 20221105102302.png]]
