## Chap.1 Introduction

### 1.1 操作系统的功能

#### 1.1.1 用户视角

#### 1.1.2 系统视角

- 资源分配器(resource allocator)
- 控制程序

#### 1.1.3 操作系统的定义

操作系统是一直运行在计算机上的程序(通常称为内核kernel); 除了内核还有系统程序和应用程序

### 1.2 计算机系统的组成

#### 1.2.1 计算机系统的运行

1. 打开电源
2. 运行初始程序/引导程序(bootstrap program)→一般位于计算机的固件(firmware), 如只读内存(Read-Only Memory, ROM)或者电可擦可编程只读内存(Electrically Erasable Programmable Read-Only Memory, EEROM)
3. 引导程序定位操作系统内核并且加到内存
4. 系统程序加到内存称为**系统进程**或**系统后台程序**, 其生命周期与内核一样(对于UNIX, 首个系统进程为"`init`"), 一旦完成这个阶段,系统就完全启动了

事件发生通过软硬件的**中断**(interrupt)来通知

#### 1.2.2 存储结构

- 


