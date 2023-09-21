#include <stdio.h>
#include <stdlib.h>

#define BR 0b0000
#define ADD 0b0001
#define LD 0b0010
#define ST 0b0011
#define JSR 0b0100
#define AND 0b0101
#define LDR 0b0110
#define STR 0b0111
#define NOT 0b1001
#define LDI 0b1010
#define STI 0b1011
#define JMP 0b1100
#define LEA 0b1110
#define HALT 0b1111
unsigned short mem[0xffff];
short regs[8];
unsigned short pc;
unsigned short ir;
unsigned short cc = 0b010;
unsigned short opcode;
unsigned short begin;
unsigned short tmp1, tmp2, tmp3;
int flag = 1;

// mem[0~ffff]->0x7777
void Init();

// move instructions into mem[]
// return the 1st addr of insts
unsigned short Load();

// execute the insts
void execute(unsigned short begin);

unsigned short str2num(char *src);

short SEXT(unsigned int inst, int len)
{
    short result = 0;
    switch (len)
    {
    case 5:
        result = inst << 11;
        result = result >> 11;
        if (result & 0b10000)
        {
            result = result | 0b1111111111100000;
        }
        break;
    case 6:
        result = inst << 10;
        result = result >> 10;
        if (result & 0b100000)
        {
            result = result | 0b1111111111000000;
        }
        break;
    case 9:
        result = inst << 7;
        result = result >> 7;
        if (result & 0b100000000)
        {
            result = result | 0b1111111000000000;
        }
        break;
    case 11:
        result = inst << 5;
        result = result >> 5;
        if (result & 0b10000000000)
        {
            result = result | 0b1111100000000000;
        }
    }
    return result;
}

inline void setcc()
{
    if (regs[tmp2] > 0)
        cc = 0b001;
    else if (regs[tmp2] == 0)
        cc = 0b010;
    else
        cc = 0b100;
    return;
}
short regnum(unsigned int inst, int highbit)
{
    unsigned short result = 0;
    switch (highbit)
    {
    case 11:
        result = inst << 4;
        result = result >> 13;
        break;
    case 8:
        result = inst << 7;
        result = result >> 13;
        break;
    case 2:
        result = inst << 13;
        result = result >> 13;
        break;
    }
    return result;
}

inline void br()
{
    tmp2 = regnum(ir, 11);
    if (tmp2 & cc)
    {
        tmp1 = SEXT(ir, 9);
        pc += tmp1;
    }
}

inline void add()
{
    if (ir & 0b100000)
    {
        tmp1 = SEXT(ir, 5);
        tmp2 = regnum(ir, 11);
        tmp3 = regnum(ir, 8);
        regs[tmp2] = regs[tmp3] + tmp1;
    }
    else
    {
        tmp1 = regnum(ir, 2);
        tmp2 = regnum(ir, 11);
        tmp3 = regnum(ir, 8);
        regs[tmp2] = regs[tmp3] + regs[tmp1];
    }
    setcc();
    return;
}

inline void ld()
{
    tmp1 = SEXT(ir, 9);
    tmp2 = regnum(ir, 11);
    tmp3 = pc + tmp1;
    regs[tmp2] = mem[tmp3];
    setcc();
    return;
}

inline void st()
{
    tmp1 = SEXT(ir, 9);
    tmp2 = regnum(ir, 11);
    tmp3 = pc + tmp1;
    mem[tmp3] = regs[tmp2];
    return;
}

inline void jsr()
{
    regs[7] = pc;
    if (ir & 0b100000000000)
    {
        tmp1 = SEXT(ir, 11);
        pc += tmp1;
    }
    else
    {
        tmp2 = regnum(ir, 8);
        pc = regs[tmp2];
    }
    return;
}

inline void and ()
{
    if (ir & 0b100000)
    {
        tmp1 = SEXT(ir, 5);
        tmp2 = regnum(ir, 11);
        tmp3 = regnum(ir, 8);
        regs[tmp2] = regs[tmp3] & tmp1;
    }
    else
    {
        tmp1 = regnum(ir, 2);
        tmp2 = regnum(ir, 11);
        tmp3 = regnum(ir, 8);
        regs[tmp2] = regs[tmp3] & regs[tmp1];
    }
    setcc();
    return;
}

inline void ldr()
{
    tmp1 = SEXT(ir, 6);
    tmp2 = regnum(ir, 11);
    tmp3 = regnum(ir, 8);
    tmp3 = regs[tmp3];
    regs[tmp2] = mem[tmp3 + tmp1];
    setcc();
    return;
}

inline void str()
{
    tmp1 = SEXT(ir, 6);
    tmp2 = regnum(ir, 11);
    tmp3 = regnum(ir, 8);
    tmp3 = regs[tmp3];
    mem[tmp3 + tmp1] = regs[tmp2];
    return;
}

inline void not()
{
    tmp1 = regnum(ir, 8);
    tmp2 = regnum(ir, 11);
    regs[tmp2] = ~regs[tmp1];

    setcc();
    return;
}

inline void ldi()
{
    tmp2 = regnum(ir, 11);
    tmp1 = pc + SEXT(ir, 9);
    tmp1 = mem[tmp1];
    regs[tmp2] = mem[tmp1];

    setcc();
    return;
}

inline void sti()
{
    tmp2 = regnum(ir, 11);
    tmp1 = pc + SEXT(ir, 9);
    tmp1 = mem[tmp1];
    mem[tmp1] = regs[tmp2];
    return;
}

inline void jmp()
{
    tmp2 = regnum(ir, 8);
    pc = regs[tmp2];
    return;
}

inline void lea()
{
    tmp1 = SEXT(ir, 9);
    tmp2 = regnum(ir, 11);
    regs[tmp2] = tmp1 + pc;
}

inline void halt()
{
    for (int i = 0; i < 8; i++)
    {
        printf("R%d = x%04hX\n", i, regs[i]);
    }
    flag = 0;
    return;
}
void Init()
{
    for (int i = 0; i < 8; i++)
    {
        regs[i] = 0x7777;
    }
    for (int i = 0; i < 0xffff; i++)
    {
        mem[i] = 0x7777;
    }
}

unsigned short str2num(char *src)
{
    short factor = 1;
    short result = 0;
    for (int i = 15; i >= 0; i--)
    {
        result += (src[i] - '0') * factor;
        factor *= 2;
    }
    return result;
}

unsigned short Load()
{
    char nowline[18];
    unsigned short linenum = 0;
    scanf("%s", nowline);
    short head = str2num(nowline);
    while (fgets(nowline, 18, stdin) != NULL)
    {
        mem[head + linenum] = str2num(nowline);
        linenum++;
    }
    return head;
}

void execute(unsigned short begin)
{
    pc = begin;
    pc++;
    while (flag)
    {
        ir = mem[pc];
        pc++;
        opcode = ir >> 12;
        switch (opcode)
        {
        case BR:
            br();
            break;
        case ADD:
            add();
            break;
        case LD:
            ld();
            break;
        case ST:
            st();
            break;
        case JSR:
            jsr();
            break;
        case AND:
            and();
            break;
        case LDR:
            ldr();
            break;
        case STR:
            str();
            break;
        case NOT:
            not();
            break;
        case LDI:
            ldi();
            break;
        case STI:
            sti();
            break;
        case JMP:
            jmp();
            break;
        case LEA:
            lea();
            break;
        case HALT:
            halt();
            break;
        }
    }
}

int main()
{
    Init();
    begin = Load();
    // printf("%x\n%x",mem[0x3000],mem[0x3001]);
    execute(begin);
    return 0;
}
