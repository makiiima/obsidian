
#include "defs.h"
#include "types.h"
#include "vm.h"
#include "mm.h"
#include "string.h"
#include "printk.h"

/* early_pgtbl: 用于 setup_vm 进行 1GB 的 映射。 */
unsigned long early_pgtbl[512] __attribute__((__aligned__(0x1000)));

void setup_vm(void) {
    /* 
    1. 由于是进行 1GB 的映射 这里不需要使用多级页表 
    2. 将 va 的 64bit 作为如下划分： | high bit | 9 bit | 30 bit |
        high bit 可以忽略
        中间9 bit 作为 early_pgtbl 的 index
        低 30 bit 作为 页内偏移 这里注意到 30 = 9 + 9 + 12， 即我们只使用根页表， 根页表的每个 entry 都对应 1GB 的区域。 
    3. Page Table Entry 的权限 V | R | W | X 位设置为 1
    */
    
    unsigned long PA = 0x80000000;
    //等值映射
    unsigned long VA1 = PA;
    //映射至高位
    unsigned long VA2 = PA + PA2VA_OFFSET;
    int index;
    // 页表的虚拟页号 9位
    index = (VA1 >> 30) & 0x1ff;
   
    //4kB one table PPN = pa>>12
    // 求出物理页号 并设置10位属性（V|R|W|X 为1）
     early_pgtbl[index] = ((PA >> 12) << 10) | 0xf;

    //同理
    index = (VA2 >> 30) & 0x1ff;
    early_pgtbl[index] = ((PA >> 12) << 10) | 0xf;
    
    printk("...setup_vm\n");
}

/* swapper_pg_dir: kernel pagetable 根目录， 在 setup_vm_final 进行映射。 */
unsigned long swapper_pg_dir[512] __attribute__((__aligned__(0x1000)));

extern char _stext[];
extern char _srodata[];
extern char _etext[];
extern char _erodata[];
extern char _sdata[];

void setup_vm_final(void) {
    memset(swapper_pg_dir, 0x0, PGSIZE);

    // No OpenSBI mapping required

    // mapping kernel text X|-|R|V
    create_mapping(swapper_pg_dir, (uint64)_stext, (uint64)_stext - PA2VA_OFFSET, (uint64)(_etext - _stext), 11);

    // mapping kernel rodata -|-|R|V
    create_mapping(swapper_pg_dir, (uint64)_srodata, (uint64)_srodata - PA2VA_OFFSET, (uint64)(_erodata - _srodata), 3);
    //MMU((uint64)_srodata);
    // mapping other memory -|W|R|V
    create_mapping(swapper_pg_dir, (uint64)_sdata, (uint64)_sdata- PA2VA_OFFSET, PHY_END + PA2VA_OFFSET - (uint64)_sdata, 7);

    // set satp with swapper_pg_dir
    uint64 _satp = 0x8000000000000000 | (((uint64)swapper_pg_dir - PA2VA_OFFSET) >> 12);
    csr_write(satp, _satp);

    // flush TLB
    asm volatile("sfence.vma zero, zero");
    printk("...setup_vm_final done!\n");
    return;
}

/* 创建多级页表映射关系 */
/*
    pgtbl 为根页表的基地址
    va, pa 为需要映射的虚拟地址、物理地址
    sz 为映射的大小 (单位为4KB)
    perm 为映射的读写权限
*/
void create_mapping(uint64 *pgtbl, uint64 va, uint64 pa, uint64 sz, int perm) {
    /*
    创建多级页表的时候可以使用 kalloc() 来获取一页作为页表目录
    可以使用 V bit 来判断页表项是否存在
    */
     // va: 9 | 9 | 9 | 12
    uint64 *second_pgtbl;
    uint64 *third_pgtbl;
    uint64 *p_second_pgtbl;
    uint64 *p_third_pgtbl;
    int i = sz / PGSIZE + 1;

    while (i--)
    {
        int vpn2 = (va >> 30) & 0x1ff;
        int vpn1 = (va >> 21) & 0x1ff;
        int vpn0 = (va >> 12) & 0x1ff;
        // top page table
        if(pgtbl[vpn2] & 0x1)
        //>>10 propretities <<12 4kB  +PA2VA :va->pa
            second_pgtbl = (uint64 *)((((uint64)pgtbl[vpn2] >> 10) << 12) );
        //若 PTE 的有效位 V 为 0,则申请一块内存空间作为新的二级页表
        //kalloc()函数获取的地址为虚拟地址，需要减去PA2VA_OFFSET才能作为页表的物理地址。
        else
        {
            second_pgtbl = (uint64 *)kalloc();
            p_second_pgtbl = (uint64)second_pgtbl - PA2VA_OFFSET;
            pgtbl[vpn2] = ((((uint64)second_pgtbl - PA2VA_OFFSET) >> 12) << 10) | 0x1;
        }
        // second page table
        if(p_second_pgtbl[vpn1] & 0x1)
            third_pgtbl = (uint64 *)((((uint64)p_second_pgtbl[vpn1] >> 10) << 12) );
        else
        {
            third_pgtbl = (uint64 *)kalloc();
            p_third_pgtbl = (uint64)third_pgtbl - PA2VA_OFFSET;
            p_second_pgtbl[vpn1] = ((((uint64)third_pgtbl - PA2VA_OFFSET) >> 12) << 10) | 0x1;
        }
        // third page table
        if( !(p_third_pgtbl[vpn0] & 0x1) )
        //store pa: >>12:offset and set properties perm 
            p_third_pgtbl[vpn0] = ((pa >> 12) << 10) | perm;
        
        //next 
        va += PGSIZE;
        pa += PGSIZE;
    }
}