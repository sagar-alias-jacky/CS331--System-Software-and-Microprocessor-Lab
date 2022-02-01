; Sagar Paul 41
; 8086 program to multiply two 16-bit numbers

ASSUME CS: CODE, DS: DATA

DATA SEGMENT
    NUM1 DW 0BFFFH
    NUM2 DW 0BBAAH
    RESULT DD ?
DATA ENDS

CODE SEGMENT
START:
MOV AX, DATA
MOV DS, AX
MOV AX, NUM1
MUL NUM2 
LEA BX, RESULT
MOV [BX], AX
MOV [BX + 2], DX
MOV AH, 4CH
INT 21H
CODE ENDS
END START