#include "defs.h"

extern main(), puts(), put_num(), ticks;
extern void clock_set_next_event(void);

void handler_s(uint64_t cause) {
  // interrupt
  unsigned long interrupt = 1ll<<63;
  if (cause & interrupt) {
    // supervisor timer interrupt
    if ((cause^interrupt) == 0x5) {
      puts("Interrupt ");
			put_num(ticks);
      puts("\n");
			clock_set_next_event();
      // 设置下一个时钟中断，打印当前的中断数目。
      // your code
    }
  }
}