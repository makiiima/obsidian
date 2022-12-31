# OS Overview

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

#### Hardware Inst

- `test_and_set`

  ```c
  bool test_and_set(boll *target){
      bool rv = *target;
      *target = true;
      return rv;
  ```

  can be used for implementing mutual exclusive
  
  ```c
  //lock was initialized to be false
  while(true){
    //entry section
    while(test_and_set(&lock))
      ;
    //critical section

    //exit section
    lock = false;

    //remainder section
  }
  ```

  above can't satisfy **bounded waiting**: there may be always some processes waiting.

  ```c
  while(true){
    //entry section
    waiting[i] = true;
    while(waiting[i] && test_and_set(&lock))
      ;
    waiting[i] = false;

    //critical section

    //exit section
    j= (i+1)%n;
    if (j == i)
      lock = false;
    else
      waiting[j] = false;
    
    //remainder section
  }
  ```

- `compare_and_swap`

  ```pseudocode
  function cas(p: pointer to int, old: int, new: int) returns boll{
    if *p != old{
      return false;
    }
    *p <-new
    return true;
  }
  ```

  ```c
  int compare_and_swap(int *value, it expected, int new_value){
    int temp = *value;
    if(*value == expected)
      *value = new_value;
    return temp;
  }
  ```

  similar to `test_and_set`

  ```c
  while(true){
    //entry section
    while(compare_and_swap(&lock, 0, 1) != 0)
      ;
    //critical section
    //exit section;
    lock = 0;
    //remainder section
  }
  ```

#### Atomic Variable

Provide atomic updates for data to avoid race condition during data updating, for example:

```c
void increment(atomic_int *v){
  int temp;
  do{
    temp = *v;
  }while(temp != compare_and_swap(v, temp, temp+1));
}
```

### Sync Examples

### Dead Lock
