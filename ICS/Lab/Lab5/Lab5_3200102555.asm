.ORIG x3000

; Load address of map data into R0
LEA R0, MAP

; Load number of rows into R1
LDR R1, R0, #0

; Load number of columns into R2
LDR R2, R0, #1

; Compute size of map data block
ADD R3, R1, R1
MUL R3, R3, R2
ADD R3, R3, #2

; Initialize loop counter
LD R4, ROW_IDX

; Initialize max path length
LD R5, MAX_PATH_LEN

; Initialize starting maximum length
ADD R6, R0, #2
LDR R7, R6, #0
ST R7, MAX_LEN

; Loop through each row
ROW_LOOP:
    ; Load address of current row
    ADD R8, R0, R4
    ADD R8, R8, #2

    ; Loop through each column in current row
    COL_LOOP:
        ; Load current height value into R9
        LDR R9, R8, #0

        ; Compute maximum length for current position
        ADD R10, R8, #2
        AND R11, R4, R4
        ADD R11, R11, R11
        ADD R11, R11, R2
        ADD R11, R11, R11
        ADD R11, R11, #MAX_LEN
        LDR R12, R10, #-R2
        ADD R13, R10, #0
        LDR R14, R10, #R2
        CALL MAX

        ; Update maximum path length if necessary
        BRn ROW_DONE
        ADD R15, R8, #MAX_LEN
        LDR R16, R15, #0
        ADD R17, R16, #1
        ST R17, MAX_PATH_LEN

        ; Store maximum length for current position
        ADD R18, R8, #MAX_LEN
        ST R16, R18, #0

        ; Move to next column
        ADD R8, R8, #4

        ; Check if all columns have been processed
        BRnp COL_LOOP

    ; Move to next row
    ADD R4, R4, #1

    ; Check if all rows have been processed
    BRnp ROW_LOOP

; Halt program
HALT

; Maximum function
MAX:
    ; Save return address
    ST R7, MAX_RET

    ; Compare current height value with neighbors
    ADD R7, R1, #0
    ADD R7, R7, R2
    ADD R7, R7, R2
    ADD R7, R7, #-1
    LDR R19, R10, R7
    ADD R7, R1, #0
    ADD R7, R7, R2
    ADD R7, R7, R2
    LDR R20, R10, R7
    ADD R7, R1, #0
    ADD R7, R7, R2
    ADD R7, R7, R2
    ADD R7, R7, #1
    LDR R21, R10, R7
    ADD R7, R1, #0
    ADD R7, R7, R2
    ADD R7, R7, #-1
    LDR R22, R12, R7
    ADD R7, R1, #0
    ADD R7, R7, #1
    ADD R7, R7, R2
    LDR R23, R14, R7

    ; Find maximum length
    ADD R7, R19, R20
    ADD R7, R7, R21
    ADD R7, R7, R22
    ADD R7, R7, R23
    ADD R7, R7, #5
    ADD R7, R7, #-1
    DIV R7, R7, #4

    ; Restore return address
    LD R7, MAX_RET

    ; Return maximum length
    RET

.END

; Data section
.ORIG x4000
MAP

.FILL #3 ; N
.FILL #4 ; M
.FILL #89 ; the map
.FILL #88
.FILL #86
.FILL #83
.FILL #79
.FILL #73
.FILL #90
.FILL #80
.FILL #60
.FILL #69
.FILL #73
.FILL #77
.END
