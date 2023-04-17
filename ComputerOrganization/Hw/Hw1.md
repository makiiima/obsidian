# Hw1
> Yunfan Li, 3200102555

## 1.2

a. Performance via Pipeling
b. Dependability via Redundancy
c. Performance via Prediction
d. Make the Common Case Fast
e. Hierarchy of Memories
f. Performance via Parallelism
g. Design for Moore's Law
h. Use Abstraction to Simplify Design

## 1.5

a.  P1: 3GHz/1.5 = 2.0 * 10^9
    P2: 2.5GHz/1.0 = 2.5 * 10^9
    P3: 4.0GHz/2.2 = 1.8 * 10^9

    So P2 has the highest performance

b.  P1  Cycles: 3GHz * 10s = 3 * 10^10
        Instructions: 3 * 10^10 / 1.5 = 2 * 10^10
    P2  Cycles: 2.5GHz * 10s = 2.5 * 10^10
        Instructions: 2.5 * 10^9 * 10 = 2.5 * 10^10
    P3  Cycles: 4.0GHz * 10^9 = 4.0 * 10^10
        Instructions: 1.8 * 10^9 * 10 = 1.8 * 10^10
c.  P1: 3GHz/(1-0.3) * 1.2 = 5.14
    P2: 2.5GHz/(1-0.3) * 1.2 = 4.28
    P3: 4.0GHz/(1-0.3) * 1.2 = 6.85

## 1.6

a.  P1: 1 * 0.1 + 2 * 0.2 + 3 * 0.5 + 3 * 0.2 = 2.6
    P2: 2

b.  P1: 1.0 * 10^6 * 2.6 = 2.6 * 10^6
    P2: 1.0 * 10^6 * 2.0 = 2.0 * 10^6

## 1.7

a.  A: CPI = (1.1s / 1.0E9) / 1ns = 1.1
    B: CPI = (1.5s / 1.2E9) / 1ns = 1.25

b.  T_A/T_B = 1.2 * 10^9 * 1.25 /(1.0 * 10^9 * 1.1) = 1.36

c.  T' = 6.0E8 * 1.1 * 1ns = 0.66s
    T'/T_A = 0.66/1.1 = 0.6
    T'/T_B = 0.66/1.5 = 0.44

## 1.13

1. 70s * 0.2 = 14s

2. 250s * 20% =50s

3. 250 * 20% = 50s > 40s
   So it is impossible.
