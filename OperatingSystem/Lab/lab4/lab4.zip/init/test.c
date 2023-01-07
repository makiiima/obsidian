#include "printk.h"
#include "defs.h"

// Please do not modify

// void test() {
//     while (1);
// }
void test() {    
    printk("idle process is running!\n");
    while(1) {}
}