# 第一章 概论

-   端系统通过通信链路(communication link)和分组交换机(packet switch)连接到一起
-   分组交换机
    -   路由器(router)
    - 链路层交换机(link-layer switch)
-   分布式应用程序: 涉及多个相互交换数据的端系统
-   套接字接口(socket interface): 规定了运行在一个端系统上的程序请求因特网基础设施向运行在另一个端系统上的特定目的地程序交付数据的方式

### 协议(protocol)

-   协议定义了在两个或多个通信实体之间交换的报文的格式和顺序, 以及报文发送和/或接收一条报文或其他事件所采取的动作

## 网络边缘

端系统也被称为主机(host), 可以进一步划分为:

-   客户(client)
-   服务器(server)

### 接入网

-   接入网: 将端系统物理连接到其边缘路由器(edge router)的网络
-   家庭接入
    -   DSL(Digital Subscriber Line, 数字用户线)
        -   电话公司, 同时承载了数据和传统的电话信号, 使用不同频率编码:
            -   高速下行信道, 50kHz-1MHz
            -   中速上行信道, 4kHZ-50kHz
            -   双向电话信道, 0-4kHz
    -   电缆
        -   有线电视公司, 需要电缆调制调节器(cable modem)
    -   FTTH(光纤到户)
        -   主动光纤网络(Active Optical Network)
        -   被动光纤网络(Passive Optical Network)
    -   拨号(慢)
    -   卫星
-   企业接入
    -   以太网
    -   WiFi
-   广域无线接入

### 物理媒体

-   物理媒体(physical medium)
    -   导引型媒体(guided media)
        -   双绞铜线
        -   同轴电缆
        -   光纤
    -   非导引型媒体(unguided media)
        -   陆地无线电信道
        -   卫星无线电信道

## 网络核心

### 分组交换

端系统彼此交换报文(message), 源将长报文划分为较小的数据块, 称之为分组(packet).在源和目的地之间, 每个分组都通过通信链路和分组交换机(packet switch)传送, 分组以最大传输速率通过通信链路

> 若经过一条R bits/s 的链路发送一个L bits的分组, 则需要L/R秒

1.  存储转发传输(store-and-forward transmission)
    
    交换机能够开始向输出链路传输该分组的第一个比特之前, 必须接收到整个分组, 故通过N条速率均为R的链路组成的路径(N-1台路由器), 从源到目的地发送一个分组的端到端时延为$$d_{端到端}=N\frac{L}{R}$$
    
2.  排队时延和分组丢失
    
    对于每条链路, 分组交换机具有一个**输出缓存**(output buffer), 也称为**输出队列**(output queue); 到达的分组如果不能通过该链路传输出去, 则要承受输出缓存的排队时延(queuing delay), 若缓存已满, 则可能会丢包(packet loss), 排队的分组或者到达的分组之一会被丢弃
    
3.  转发表和路由选择协议
    
    每个端系统具有一个IP地址, 分组的首部包含了目的地的IP地址, 当一个分组到达路由器时, 路由器检查目的地地址的一部分并转发给另一个路由器, **转发表**(forwarding table)用于将目的地址(或其一部分)映射为输出链路, **路由转发协议**(routing protocol)用于自动地设置这些转发表
    

### 电路交换(circuit switching)

当两台主机需要通信时, 直接在两台主机之间创建一条专用的**端到端连接**(end-to-end connection), 每条端到端连接均分链路的总传输容量

1.  电路交换网络中的复用
    -   频分复用(Frequency-Division Multiplexing, FDM)
    -   时分复用(Time-Division Mutiplexing, TDM)
2.  分组交换性能大体上优于电路交换

## 分组交换网中的时延, 丢包, 吞吐量

### 时延

-   处理时延(processing delay)
    
-   排队时延(queuing delay)
    
-   传输时延(transmission delay)
    
    路由器推出分组所需要的时间, 是分组长度和链路传输速率的函数, 与两台路由器之间的距离无关
    
-   传播时延(propagation delay)
    
    取决于链路的物理媒体和路由之间的距离
    

dnodal=dproc+dqueue+dtrans+dpropd_{nodal}=d_{proc}+d_{queue}+d_{trans}+d_{prop} d​nodal​​=d​proc​​+d​queue​​+d​trans​​+d​prop​​

### 排队时延和丢包

分组到达队列的平均速率(分组/秒)=a

传输速率(bps)=R

分组大小(假定)=L

假设该队列非常大, 能容纳无线数量的比特,则

流量强度(traffic\ intensity)=\frac{La}{R}

-   如果流量强度>1, 则到达速率超过输出速率, 队列将趋向于无限增加, 排队时延将趋向无穷大, 所以**流量强度不能>1**
-   考虑流量强度≤1的情况
    -   周期性到达: 如果每L/R秒到达一个分组, 则每个分组都降到打一个空队列, 不会有排队时延
    -   突发形式到达: 如果每(L/R)*N秒同时到达N个分组, 则第一个分组没有排队时延, 第二个分组就有L/R秒的排队时延, 第n个传输的分组具有(n-1)*L/R的排队时延

![](https://secure2.wostatic.cn/static/cYduQ3PXBK5Rrv3goPT6WG/image.png?auth_key=1666070190-iwi8cXF8e9NQdQYZECuoVY-0-7cc1006aacd47776b7a887feae2d5541)

### 端到端时延

假设源主机和目的主机之间有N-1台路由器, 网络无拥塞

dend−end=N(dproc+dtrans+dprop)d_{end-end}=N(d_{proc}+d_{trans}+d_{prop}) d​end−end​​=N(d​proc​​+d​trans​​+d​prop​​)

### 吞吐量

-   瞬时吞吐量(instantaneous throughput)
-   平均吞吐量(average throughput)

服务器到路由速率RsR_sR​s​​, 路由到客户机速率RcR_cR​c​​, 则吞吐量为min{Rc,Rs}min\{R_c,R_s\}min{R​c​​,R​s​​}(不考虑排队积压)

由于网络核心链路的速率很高, 所以吞吐量限制因素通常是接入网

## 协议层级及其服务模型

### 分层(layer)的体系结构

一层向上一层提供服务(service), 称为服务模型(service model)

网络层是硬件和软件实现的混合体, 一个第n层协议也分布在构成该网络的端系统, 分组交换机和其他组件中

协议分层具有概念化和结构化的优点

综合起来, 各层的所有协议被称为协议栈(protocol stack), 因特网的协议栈由5个层次组成

1.  应用层
    -   网络应用程序及他们的应用层协议存留的地方
        -   HTTP: Web文档的请求和传送
        -   SMTP: 电子邮件报文的传输
        -   FTP: 两个端系统之间的文件传送
2.  运输层
    -   在应用程序端点之间传送应用层报文
        -   TCP: 面向连接, 确保传递和流量控制, 将长报文划分为短报文, 提供拥塞控制机制
        -   UDP: 无连接服务
3.  网络层(IP层)
    -   负责将数据报(datagram, 网络层分组)从一台主机移动到另一台主机
        -   IP
4.  链路层(frame, 帧)
    -   将分组从一个节点移动到路径上的下一个节点
        -   WiFi
        -   以太网
        -   DOCSIS
5.  物理层
    -   将帧中的一个个比特从一个结点移动到下一个节点

#### OSI模型

1.  应用层
2.  **表示层**
    -   使通信的应用能够解释交换数据的含义, 包括数据压缩, 数据加密, 数据描述
3.  **会话层**
    -   数据交换的定界和同步, 包括建立检查点和恢复方案
4.  运输层
5.  网络层
6.  数据链路层
7.  物理层

### 封装(encapsulation)

![](https://secure2.wostatic.cn/static/9khSgXZ58AD2zpzaGKdvqc/image.png?auth_key=1666070192-96KvvFN5cUEH2BLcepoCYx-0-5b52d17b441b3c5314a738e1b9ea5e32)

```Mermaid
flowchart 
      A(应用层报文, application-layer massage)
      B(运输层报文段, transport-layer segment)
      C(网络层数据报, network-layer datagram)
      D(链路层帧, link-layer frame)
      E(物理层)
      A--传送+封装-->B--传递+封装-->C--传递+封装-->D-->E
```

在每一层, 一个分组具有两种类型的字段: 首部字段和有效载荷字段(payload field), 有效载荷通常来自上一层的分组

# 第二章 应用层