; Sagar Paul 41
; 8086 program to add two 32-bit numbers

ASSUME CS: CODE, DS: DATA

DATA SEGMENT
    NUM1 DD 67975423H
    NUM2 DD 5834B758H
    RESULT DD ?
    DATA ENDS

CODE SEGMENT
START:
    MOV AX, DATA
    MOV DS, AX
    CLC
    MOV CX, 0000H
    MOV AX, WORD PTR NUM1
    MOV BX, WORD PTR NUM2
    ADD AX, BX
    MOV WORD PTR RESULT, AX
    MOV AX, WORD PTR NUM1 + 2
    MOV BX, WORD PTR NUM2 + 2
    ADC AX, BX
    JNC NEXT
    INC CX
NEXT:
    MOV WORD PTR RESULT + 2, AX
    MOV WORD PTR RESULT + 4, CX
    MOV AH, 4CH
    INT 21H
CODE ENDS
END START