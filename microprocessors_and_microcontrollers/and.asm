; Sagar Paul 41
; 8086 program to perform AND operation on two operands

ASSUME CS: CODE

CODE SEGMENT
START:
    MOV AX, 1234H
    MOV BX, 5678H
    AND AX, BX
    MOV AH, 4CH
    INT 21H
CODE ENDS
END START