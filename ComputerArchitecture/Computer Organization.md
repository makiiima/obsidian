# Chap.2 Instructions
## 2.5 计算机中的指令表示
- 指令格式：由二进制数字字段组成的指令表示形式
- 机器语言：用于计算机系统内通信的二进制表示
- RISC-V字段(R型)
  ![[attachments/Pasted image 20221112162747.png]]
- I型
  ![[attachments/Pasted image 20221112162852.png]]
- S型
  ![[attachments/Pasted image 20221112163131.png]]
## 2.6 逻辑操作
![[attachments/Pasted image 20221112165314.png]]
```riscv
slli x11,x19,4    //reg x11 = reg x19 << 4 bits
```
`srai`算数右移不是用0填充左边的位，而是用原来的符号位填充
为了保持三操作数格式，使用`xor`来取代`not`
`not == xor 1111...1111`

## 2.7 用于决策的指令
```riscv
beq rs1,rs2,L1 //if rs1==rs2, goto L1

bnq rs1,rs2,L1 //if rs1!=rs2, goto L1
```

### 循环
> 以分支结尾的指令序列称为**基本块**: 除了在序列起始处, 没有分支目标和分支标签

边界检查:
为了检查是否0 <= x < y(检测数组下标是否越界)
```riscv
begu x20,x11, IndexOutOfBounds// if x20>= x11 or x20<0, goto IndexOutOfBounds
```

case/switch语句使用编码形成指令序列的地址表的方式实现
分支地址表： 包含了不同指令序列地址的表

## 2.8 计算机硬件对过程的支持
执行过程的六个步骤
1. 将参数放在构成可以访问到的位置
2. 将控制转交给过程
3. 获取过程所需的存储资源
4. 执行所需的任务
5. 将结果值放在调用程序可以访问到的位置
6. 将控制返回到初始点，因为过程可以从程序的多个点调用
>RISCV软件为过程调用分配寄存器时：
>    `x10-x17`:八个参数寄存器，用于传递参数或返回值
>    `x1`：一个返回地址寄存器，用于返回初始点

RISCV还包含一个仅作用于过程的指令：跳转到某个地址的同事将下一条指令的地址保存到目标寄存器`rd`
- 跳转-链接指令`jal`
```riscv
jal x1,ProcedureAddress //jump to ProcedureAddress and write return address to x1
```
为了支持`case`跳转，使用简洁跳转
```riscv
jalr x0,0(x1)
```



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
![[attachments/Pasted image 20221105102302.png]]

`beq`指令有三个操作数，两个寄存器用于比较是否相等，另一个是12位偏移量
    `beq x1,x2,offset`
- 计算分值目标地址的基址是分支指令所在地址
- 计算分支目标地址时，将偏移量左移1位以表示半字为单位的偏移量，这样偏移量的有效范围就扩大到两倍 
