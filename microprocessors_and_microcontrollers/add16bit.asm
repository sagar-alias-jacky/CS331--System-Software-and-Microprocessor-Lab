; SAGAR PAUL 41
; 8086 PROGRAM TO ADD TWO 16 BIT NUMBERS

ASSUME CS:CODE, DS:DATA

DATA SEGMENT
    NUM1 DW 2567H
    NUM2 DW 9213H
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
    ADD AX, BX
    JNC NEXT
    INC CX
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
