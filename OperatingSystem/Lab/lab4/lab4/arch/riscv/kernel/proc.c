#include "proc.h"
#include "mm.h"
#include "rand.h"
#include "printk.h"
#include "defs.h"

extern void __dummy();

struct task_struct* idle;           // idle process
struct task_struct* current;        // 指向当前运行线程的 `task_struct`
struct task_struct* task[NR_TASKS]; // 线程数组, 所有的线程都保存在此

void task_init() {
    // 1. 调用 kalloc() 为 idle 分配一个物理页
    // 2. 设置 state 为 TASK_RUNNING;
    // 3. 由于 idle 不参与调度 可以将其 counter / priority 设置为 0
    // 4. 设置 idle 的 pid 为 0
    // 5. 将 current 和 task[0] 指向 idle

    /* YOUR CODE HERE */
    uint64 addr_idle = kalloc();
    idle = (struct task_struct*)addr_idle;
    idle->state = TASK_RUNNING;
    idle->counter = idle->priority = 0;
    idle->pid = 0;

    current = task[0] = idle;

    // 1. 参考 idle 的设置, 为 task[1] ~ task[NR_TASKS - 1] 进行初始化
    // 2. 其中每个线程的 state 为 TASK_RUNNING, counter 为 0, priority 使用 rand() 来设置, pid 为该线程在线程数组中的下标。
    // 3. 为 task[1] ~ task[NR_TASKS - 1] 设置 `thread_struct` 中的 `ra` 和 `sp`,
    // 4. 其中 `ra` 设置为 __dummy （见 4.3.2）的地址,  `sp` 设置为 该线程申请的物理页的高地址

    /* YOUR CODE HERE */
    for(int i = 1; i < NR_TASKS; i++){
        uint64 task_addr = kalloc();
        task[i] = (struct task_struct*)task_addr;
        task[i]->state = TASK_RUNNING;
        task[i]->counter = 0;
        task[i]->priority = rand() % 10 + 1;
        task[i]->pid = i;
        task[i]->thread.ra = (uint64)__dummy;
        task[i]->thread.sp = task_addr + 4096;
    }

    printk("...proc_init done!\n");
}

void dummy() {
    uint64 MOD = 1000000007;
    uint64 auto_inc_local_var = 0;
    int last_counter = -1;
    while(1) {
        if (last_counter == -1 || current->counter != last_counter) {
            last_counter = current->counter;
            auto_inc_local_var = (auto_inc_local_var + 1) % MOD;
            // printk("[PID = %d] is running. auto_inc_local_var = %d\n", current->pid, auto_inc_local_var);
            printk("[PID = %d] is running. thread space begin at 0x%016lx\n", current->pid, current);
        }
    }
}

extern void __switch_to(struct task_struct* prev, struct task_struct* next);

void switch_to(struct task_struct* next) {
    if (next == current) return; // 同一个线程无需处理
    else {
        struct task_struct* current_saved = current;
        current = next;  //切换
        __switch_to(current_saved, next);
    }
}

void do_timer(void) {
    // 1. 如果当前线程是 idle 线程 直接进行调度
    // 2. 如果当前线程不是 idle 对当前线程的运行剩余时间减1 若剩余时间仍然大于0 则直接返回 否则进行调度
    if (current == task[0]) schedule();//直接调度
    else {
        current->counter = current->counter-1;
        if (current->counter <= 0) schedule();
    }
}

// #define DSJF
void schedule(void){
    #ifdef DSJF 
    uint64 mini_count;
    int next;
    int flag;
   while(1){
        mini_count = 0xFFFFFFFFFFFFFFFF;
        flag = 1;
        for(int i = 1; i < NR_TASKS; i++){
            if(task[i]->counter == 0)
                continue;
            else
                flag = 0;
            if(task[i]->counter <= mini_count)
                next = i, mini_count = task[i]->counter;
        }
        if(!flag)
            break;
        for(int i = 1; i < NR_TASKS; i++){
            task[i]->counter = rand();
            printk("SET [PID = %d COUNTER = %d]\n", i, task[i]->counter);
        }
    }
    printk("\nswitch to [PID = %d COUNTER = %d]\n", task[next]->pid,  task[next]->counter);
	switch_to(task[next]);
    #endif

    #ifdef DPRIORITY
    int next, flag;
    uint64 max_priority;
      while(1){
        max_priority = 0;
        flag = 1;
        for(int i = 1; i < NR_TASKS; i++){
            if(task[i]->counter == 0)
                continue;
            else
                flag = 0;
            if(task[i]->priority >= max_priority)
                next = i, max_priority = task[i]->priority;
        }
        if(!flag)
            break;
        for(int i = 1; i < NR_TASKS; i++){
            task[i]->counter = (task[i]->counter >> 1) + task[i]->priority;
            // task[i]->priority = rand();
            // task[i]->counter = rand();
            printk("SET [PID = %d PRIORITY = %d COUNTER = %d]\n", i, task[i]->priority, task[i]->counter);
        }
    }
    printk("\nswitch to [PID = %d PRIORITY = %d COUNTER = %d]\n", task[next]->pid, task[next]->priority, task[next]->counter);
	switch_to(task[next]);
    #endif
}
