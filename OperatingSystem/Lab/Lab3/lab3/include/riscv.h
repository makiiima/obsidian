//内联汇编中输入输出限制符"i"表示立即数

// 将val的值读入reg中
#define write_csr(reg, val)                                     \
  ({                                                            \
    if (__builtin_constant_p(val) && (unsigned long)(val) < 32) \
      asm volatile("csrwi " #reg ", %0" ::"i"(val));            \
    else                                                        \
      asm volatile("csrw " #reg ", %0" ::"r"(val));             \
  })

// 将reg的值读出，存在__tmp变量中
#define read_csr(reg)                             \
  ({                                              \
    unsigned long __tmp;                          \
    asm volatile("csrr %0, " #reg : "=r"(__tmp)); \
    __tmp;                                        \
  })

// 将reg的值读出并存入__tmp变量中，且对bit中的每一位1，将reg中的相同位设置为1
#define set_csr(reg, bit)                                               \
  ({                                                                    \
    unsigned long __tmp;                                                \
    if (__builtin_constant_p(bit) && (unsigned long)(bit) < 32)         \
      asm volatile("csrrsi %0, " #reg ", %1" : "=r"(__tmp) : "i"(bit)); \
    else                                                                \
      asm volatile("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "r"(bit));  \
    __tmp;                                                              \
  })

// 将reg的值读出并存入__tmp变量中，且对bit中的每一位0，将reg中的相同位设置为0
#define clear_csr(reg, bit)                                             \
  ({                                                                    \
    unsigned long __tmp;                                                \
    if (__builtin_constant_p(bit) && (unsigned long)(bit) < 32)         \
      asm volatile("csrrci %0, " #reg ", %1" : "=r"(__tmp) : "i"(bit)); \
    else                                                                \
      asm volatile("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "r"(bit));  \
    __tmp;                                                              \
  })

#define rdtime() read_csr(time)
#define rdcycle() read_csr(cycle)
#define rdinstret() read_csr(instret)