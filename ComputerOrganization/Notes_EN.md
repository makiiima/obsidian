# Computer Organization

## Chapter3

### 3.2 Addition and Subtraction

- Overflow Detection
| Operation    | Operand A    | Operand B    | Result indicatiing overflow    |
|---------------- | --------------- | --------------- | --------------- |
| A+B   | >=0    | >=0    | <0    |
| A+B   | <0   | <0   | >=0   |
| A-B   | >=0   | <0   | <0   |
| A-B   | <0   | >=0   | >=0   |

> saturating operations: when a calculation overflows, the result is set to the largest positive number or the most negative number, rather than a modulo calculation as in two’s complement arithmetic
> Speed up: *carry lookahead*

### 3.3 Multiplication



