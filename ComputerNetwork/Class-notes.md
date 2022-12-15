## Introduction

### The OSI Reference Model

- Physical Layer ->bit, byte
- Datalink  -> frame
- Network -> packet
- Transport, Session, Presentation, Application -> message
统称为PDU, protocol data unit

### The TCP/IP Reference Model

常见协议
- Link: HTTP. SMTP, RTP, DNS
- Internet: TCP, UDP
- Transport: IP, ICMP
- Application: DSL, SONET, 802.11, Ethernet

### The Model Used in the Book

1. Physical
2. Datalink
3. Network
4. Transport
5. Application

## Chap.2 The Physical Layer

### The Maximum Data Rate of a Channel

- Nyquist's theorem(理论情况, 无噪声)
    Maximum data rate = $2Blog_2  V$ bits/sec
    B是带宽, V是每个信号对应的比特数(多进制编码)
- Shannon's formula for capacity of a noisy channel
    Maximum data rate = $Blog_2(1+S/N)$ bits/sec
    S/N -> signal/noise, 信噪比

### Multiplexing

- Frequency Division Multiplexing
- Time Division Multiplexing
- Code Division Multiplexing
- Wavelength Division Multiplexing

### Design Goals

- Reliability
-  

