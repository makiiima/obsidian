## 2 What is program and compiler

### program is finite-state machine

- state = heap + stack
- initial state = first line in `main()`
- transform = execute the first command

## 3 Multiprocessor programming

### Concurrency

The basic unit: thread
Multiple execution streams of shared memory
- execution streams have independent stack/regs
- share the whole memory(the pointers can reference each other)
