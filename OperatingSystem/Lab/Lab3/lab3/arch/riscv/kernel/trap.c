#include "defs.h"

extern main(), puts(), put_num(), ticks, do_timer();

extern void clock_set_next_event(void);

void handler_s(uint64_t cause, uint64_t epc) {
  // interrupt
  unsigned long interrupt = 1ll<<63;
  if (cause & interrupt) {
    // supelab3/arch/riscv/kernel/trap.crvisor timer interrupt
    if ((cause^interrupt) == 0x5) {
      // run do_timer() per 10 ticks, which means 0.1s.
      if (ticks % 10 == 0) {
        do_timer();
      }
      clock_set_next_event();
    }
  }
  return;
}
