.ORIG x3000

    ; Load the addresses of the two strings
    LEA R0, string1
    LEA R1, string2

    ; Initialize an array for character counts
    AND R2, R2, #0        ; Clear the counter array

    ; Loop through string1 to count characters
    LDR R3, R0, #0        ; Load the first character of string1

    COUNT_LOOP1:
        ADD R4, R3, #0    ; Copy the character to R4
        JSR CHAR_TO_INDEX ; Convert character to index (a: 97 -> 0, b: 98 -> 1, ..., z: 122 -> 25)
        ADD R5, R2, R0    ; Calculate the address of the counter for the character
        LDR R6, R5, #0    ; Load the current count of the character
        ADD R6, R6, #1    ; Increment the count
        STR R6, R5, #0    ; Store the updated count

        ADD R0, R0, #1    ; Move to the next character
        LDR R3, R0, #0    ; Load the next character
        BRz COUNT_DONE1   ; If null terminator is encountered, move to the next phase
        BR COUNT_LOOP1

    ; Loop through string2 to count characters
    LDR R3, R1, #0        ; Load the first character of string2

    COUNT_LOOP2:
        ADD R4, R3, #0    ; Copy the character to R4
        JSR CHAR_TO_INDEX ; Convert character to index (a: 97 -> 0, b: 98 -> 1, ..., z: 122 -> 25)
        ADD R5, R2, R0    ; Calculate the address of the counter for the character
        LDR R6, R5, #0    ; Load the current count of the character
        ADD R6, R6, #-1   ; Decrement the count
        STR R6, R5, #0    ; Store the updated count

        ADD R1, R1, #1    ; Move to the next character
        LDR R3, R1, #0    ; Load the next character
        BRz COMPARE       ; If null terminator is encountered, move to compare phase
        BR COUNT_LOOP2

    ; Compare the character counts
    COMPARE:
        AND R6, R6, #0    ; Clear R6 for comparison
        ADD R4, R2, #0    ; Copy the counter array's address to R4

        COMPARE_LOOP:
            LDR R5, R4, #0     ; Load the current count of a character
            ADD R6, R6, R5     ; Add the count to R6
            ADD R4, R4, #1     ; Move to the next character's count
            BRn NOT_ANAGRAM    ; If any count is negative, it's not an anagram
            BRzp COMPARE_LOOP

    ; Output "YES" if it's an anagram
    OUTPUT_YES:
        LEA R0, yes_msg
        TRAP x22           ; Output the string
        BR DONE

    ; Output "NO" if it's not an anagram
    NOT_ANAGRAM:
        LEA R0, no_msg
        TRAP x22           ; Output the string
        BR DONE

    ; Halt the program
    DONE:
        TRAP x25           ; Halt the program

    ; Character count array
    .BLKW 26

    ; Subroutine to convert character to index
    CHAR_TO_INDEX:
        ADD R0, R4, #-97  ; Convert lowercase letter to an index (a: 97 -> 0, b: 98 -> 1, ..., z: 122 -> 25)
        RET

    ; Data section
    yes_msg     .STRINGZ "YES\n"
    no_msg      .STRINGZ "NO\n"
    string1     .STRINGZ "listen"
    string2     .STRINGZ "silent"

.END
