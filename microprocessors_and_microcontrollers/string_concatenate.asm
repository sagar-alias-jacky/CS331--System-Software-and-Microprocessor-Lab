; Sagar Paul 41
; 8086 program to perform string concatenation

ASSUME CS:CODE,DS:DATA

DATA SEGMENT
    MSG1 DB 'Hello$'
    MSG2 DB 'World$'
DATA ENDS

CODE SEGMENT
START:
    MOV AX,DATA
    MOV DS,AX
    LEA SI,MSG1
    LEA DI,MSG2
    MOV AL,'$'
    UP:
    CMP AL,[SI]
    JZ NEXT
    INC SI
    JMP UP
    NEXT: CMP AL,[DI]
    JZ EXIT
    MOV BL,[DI]
    MOV[SI],BL
    INC SI
    INC DI
    JMP NEXT
    EXIT: MOV [SI],AL
    LEA DX,MSG1
    MOV AH,9H
    INT 21H
    MOV AH,4CH
    INT 21H
CODE ENDS
END START