#include "printk.h"
#include "sbi.h"
#include "defs.h"
extern void test();

extern char _stext[];
extern char _srodata[];
int start_kernel() {
  printk("_stext = %ld\n", *_stext);
  *_stext = 0;
  printk("_srodata = %ld\n", *_srodata);
     //  puti(2022);
    //  puti(0);
    //  puti(-1);
  //   puts("Hello RISC-V\n");
    //sbi_ecall(0x1,0x0,0x30,0,0,0,0,0);
    // uint64 t = csr_read(sstatus);
    // puti(t);
    // uint64 t = 2022;
    // csr_write(sscratch,t);
    // uint64 t1 = csr_read(sscratch);
    // puti(t1);
   // printk("%s","123");
    test(); // DO NOT DELETE !!!

	return 0;
}
