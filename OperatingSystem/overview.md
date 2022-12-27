## Process Synchronization

### Sync Tools

why
- race condition
- Cooperating Process: share some data or address space, the concurrent access can cause data inconsistency
- critical section: the code piece that may change some data that is shared with other process

```pseudocode
while (true){
    entry section

    	critical section

    exit section

    	remainder section
}
```

The solution to critical-section problem must satisfy:

1. Mutual exclusion(互斥): no two processes can run critical section in the same time
2. Progress(前进): the system is running, not blocked by some critical-section problem(不在临界区的进程不能阻止另一个进程进入临界区)
3. Bounded waiting(有限等待): there are finite waiting time for any process

- preemptive kernel
- non-preemptive kernel

#### Peterson's Solution

satisfy two tasks synchronization

```c
int turn;
bool flag[2];

void foo(){
    while (true) {
        flag[i] = true;
        turn = 1-i;
        
        while(flag[1-i]&&turn==1-i) ;
        
        flag[i]=false;
    }
}
```

- Reordering -> Memory barrier
- Memory model
  - **Strongly ordered**, where a memory modification on one processor is immediately visible to all other processors
  - **Weakly ordered**, where modifications to memory on one processor may not be immediately visible to other processors

#### Hardware Inst.

- `test_and_set`
- `compare_and_swap`


### Sync Examples

### Dead Lock
