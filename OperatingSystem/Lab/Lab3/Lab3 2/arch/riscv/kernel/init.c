#include "riscv.h"

extern void clock_init(void);
extern void task_init(void);

void intr_enable(void) {
  // 设置 sstatus[sie] = 1, 打开 s 模式的中断开关
  unsigned long bit = 2;
  set_csr(sstatus, bit);
}

void intr_disable(void) {
  // 设置 sstatus[sie] = 0, 关闭 s 模式的中断开关
  unsigned long bit = 2;
  clear_csr(sstatus, bit);
}

void idt_init(void) {
  extern void trap_s(void);
  // 向 stvec 寄存器中写入中断处理后跳转函数的地址
  unsigned long location = &trap_s;
  write_csr(stvec, location);
}

void init(void) {
  idt_init();
  intr_enable();
  clock_init();
  task_init();
}
