; Sagar Paul 41
; 8086 program to subtract two 16-bit numbers

ASSUME CS: CODE, DS: DATA

DATA SEGMENT
    NUM1 DW 1000H
    NUM2 DW 1002H
    RESULT DW 0000H
DATA ENDS

CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS, AX
    MOV AX, NUM1
    MOV BX, NUM2
    CLC
    MOV CX, 0000H
    SUB AX, BX
    JNC NEXT
    INC CX
    NOT AX
    ADD AX, 0001H
NEXT:
    MOV DI, OFFSET RESULT
    MOV [DI], AX
    INC DI
    INC DI
    MOV [DI], CX
    MOV AH, 4CH
    INT 21H
CODE ENDS
END START