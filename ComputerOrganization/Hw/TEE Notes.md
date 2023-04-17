# TEE Notes

## Introduction

- Trusted Excution Environment, TEE
- Rich Execution Environment, REE
- Trusted Application, TA
- Trusted Computing Base, TCB -> virtulization

## 关键技术

- 安全启动, secure boot
    - monitor/SoC
- 完整性证明, integrity attestation
- 存储隔离, memory isolation
    - 分离核&不可篡改
    - 需要硬件支持

## 典型设计

### Intel SGX

- enclave, 飞地

enclave内部无需相信自身以外的软件栈(REE, drivers...)

- 处理器保留内存, Processor Reserved Memory, PR M
    - <=128MB, 启动时保留
    - Enclave Page Cache, EPC
        - 大小为94MB, 专门为enclave容器分配空间
        - 无论一个enclave容器占据多少虚拟地址空间, 物理页面只能在EPC当中分配
    - enclave 外部的应用程序不能访问 enclave 内存;enclave 内部的代码在 EPC 范围内只能访问属于自己的内存区域，不能访问属于其他 enclave 的内 存区域;对于 PRM 以外的内存，则按照系统中其他的保护机制进行访问。
    - Enclave Page Cache Map, EPCM