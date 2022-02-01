; Sagar Paul 41
; 8086 program to perform NOT operation on an operand

ASSUME CS: CODE

CODE SEGMENT
START:
    MOV AX, 1234H
    NOT AX
    MOV AH, 4CH
    INT 21H
CODE ENDS
END START