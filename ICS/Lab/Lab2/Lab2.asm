.ORIG x3000
; addr .FILL x4000
    INIT:
        AND R0, R0, 0
        AND R1, R1, 0
        AND R2, R2, 0
        AND R3, R3, 0
        AND R4, R4, 0
        AND R5, R5, 0
        AND R6, R6, 0
        AND R7, R7, 0
    LOAD1:
        LDI R1, addr1; R1 stores str1_addr
        LD R2, addr3; R2 stores cnt's addr
    
    
    LOOP1:
        ;if mem[R1]=='\0' break
        LDR R3, R1, #0; R3=mem[R1] as the char now
        ADD R4, R3, #0
        BRz LOAD2
        ;else if mem[R1]==' ' continue
        LD R4, base2
        ADD R5, R3, R4
        BRz END_LOOP1
        ;else if R3 is uppercase
        LD R4, base
        ADD R5, R4, R3
        BRn UPPER1
        BRzp LOWER1
    
    UPPER1:;R3+=32
        LD R4, base4
        ADD R3, R3, R4
        
    
    LOWER1:;cnt[R3-97]++
        LD R4, base
        ADD R3, R3, R4
        ADD R5, R3, R2;R5->cnt[i]
        LDR R6, R5, #0
        ADD R6, R6, #1
        STR R6, R5, #0
        
    END_LOOP1:
        ADD R1, R1, #1
        BRnzp LOOP1
        
    LOAD2:
        LDI R1, addr2; R1 stores str1_addr
        LD R2, addr3; R2 stores cnt's addr
        
    LOOP2:
        ;if mem[R1]=='\0' break
        LDR R3, R1, #0; R3=mem[R1] as the char now
        ADD R4, R3, #0
        BRz CHECK
        ;else if mem[R1]==' ' continue
        LD R4, base2
        ADD R5, R3, R4
        BRz END_LOOP2
        ;else if R3 is uppercase
        LD R4, base
        ADD R5, R4, R3
        BRn UPPER2
        BRzp LOWER2
    
    UPPER2:;R3+=32
        LD R4, base4
        ADD R3, R3, R4
        
    
    LOWER2:;cnt[R3-97]++
        LD R4, base
        ADD R3, R3, R4
        ADD R5, R3, R2;R5->cnt[i]
        LDR R6, R5, #0
        ADD R6, R6, #-1
        STR R6, R5, #0
        
    END_LOOP2:
        ADD R1, R1, #1
        BRnzp LOOP2
        
    CHECK:                                                                                          
    
    HALT
    
    addr1   .FILL str1_addr
    addr2   .FILL str2_addr
    addr3   .FILL cnt
    base    .FILL #-97; 'a' ASCII value
    base2   .FILL #-32; ' ' ASCII value
    base3   .FILL #-65; 'A' ASCII value
    base4   .FILL #32
.END
        
.ORIG x4000
    str1_addr    .FILL str1
    str2_addr    .FILL str2
    str1    .STRINGZ "abcdef gHiJklmnopqrstuvwxyz"
    str2    .STRINGZ ""
    cnt  .BLKW 26
        .FILL 0
.END


