.ORIG x3000 ; code start

INIT:
    AND R0, R0, #0
    AND R1, R1, #0
    AND R2, R2, #0
    AND R3, R3, #0
    AND R4, R4, #0
    AND R5, R5, #0
    AND R6, R6, #0
    AND R7, R7, #0

SET_PTR:
    LD R5 LPTR; R5 points at xA001
    LD R6 RPTR; R6 points at xA000
    LD R3 POPPED;

INPUT:
    GETC
    OUT;echo
    
    ADD R1 R0 #-10; if press ENTER
    BRz PRINT
    
    LD R1 PLUS
    ADD R1 R0 R1; if left push
    BRz LPUSH
    
    LD R1 MINUS
    ADD R1 R0 R1; if left pop
    BRz LPOP
    
    LD R1 LP; if right push
    ADD R1 R0 R1;
    BRz RPUSH
    
    LD R1 RP; if right pop
    ADD R1 R0 R1;
    BRz RPOP
    
    BRnzp INPUT ; jump back to start
    
PRINT:
    LD R1 POPPED;R1 is moving ptr of POPPED 
    ADD R2 R3 #0;R2 := R3
    NOT R2 R2;
    ADD R2 R2 #1; R2 := -R3
PPLOOP:
    ADD R4 R1 R2; R4 := R1 + R2 = R1 - R3
    BRz TOHALT
    LDR R0 R1 #0; R0 <- mem[R1]
    OUT 
    ADD R1 R1 #1

    BRnzp PPLOOP
    
TOHALT:    
    HALT


LPUSH:
    GETC
    OUT; echo
    ADD R5 R5 #-1;move left ptr to left
    STR R0 R5 #0;mem[R5] <- R0
    BRnzp success_exit; 
    
LPOP:
    ST R1 SaveR1;
    ST R2 SaveR2;
    
    
    NOT R1 R6
    ADD R1 R1 #1; R1 := -R6
    ADD R2 R5 R1; R2 := R5 + R1 = R5 - R6
    BRp fail_exit;if R5 > R6 then stack is empty
    
    LDR R4 R5 #0;R4 <- mem[R6]
    STR R4 R3 #0;mem[R3] <- R4
    ADD R3 R3 #1;
    
    ADD R5 R5 #1;move left ptr to right
    BRnzp success_exit

RPUSH:
    TRAP x20
    TRAP x21;
    
    ADD R6 R6 #1;move right ptr to right
    STR R0 R6 #0;mem[R6] <- R0
    BRnzp success_exit;
    
RPOP:
    ST R1 SaveR1;
    ST R2 SaveR2;
    
    NOT R1 R6
    ADD R1 R1 #1; R1 := -R6
    ADD R2 R5 R1; R2 := R5 + R1 = R5 - R6
    BRp fail_exit;if R5 > R6 then stack is empty
    
    LDR R4 R6 #0;R4 <- mem[R6]
    STR R4 R3 #0;mem[R3] <- R4
    ADD R3 R3 #1;
    
    ADD R6 R6 #-1;move right ptr to left
    BRnzp success_exit
    

success_exit:
    LD R1 SaveR1
    LD R2 SaveR2
    BRnzp INPUT

fail_exit:
    LD R1 SaveR1
    LD R2 SaveR2
    LD R4 UNDERLINE
    STR R4 R3 #0;mem[R3] <- R4
    ADD R3 R3 #1;
    BRnzp INPUT
    

    LPTR  .FILL x4001
    RPTR  .FILL x4000
    POPPED  .FILL x5000; the popped elements
    
    PLUS .FILL #-43; ascii of +
    MINUS .FILL #-45; ascii of -
    LP .FILL #-91; ascii of [
    RP .FILL #-93; ascii of ]
    SaveR1  .FILL x6000
    SaveR2  .FILL x6001
    SaveR3  .FILL x6002
    UNDERLINE  .FILL #95; ascii of _
    
    
.END ; code end