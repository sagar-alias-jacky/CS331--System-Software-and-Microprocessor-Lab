; Sagar Paul 41 
; 8086 program to search whether a character is present in a string

ASSUME CS:CODE, DS:DATA

DATA SEGMENT
    STR1 DB 'HELLO WORLD$'
    MSG DB 'CHARACTER FOUND!$'
    MSG1 DB 'CHARACTER NOT FOUND!$'
DATA ENDS

CODE SEGMENT
START:
    MOV AX,DATA
    MOV DS,AX
    LEA SI,STR1
    MOV AL,'F'
    MOV DL,'$'
    COM: 
    CMP AL,[SI]
    JZ NEXT
    CMP DL,[SI]
    JZ NEXT1
    INC SI
    JMP COM
    NEXT1:
    LEA DX,MSG1
    MOV AH,9H
    INT 21H
    JMP OVER
    NEXT: LEA DX,MSG
    MOV AH,9H
    INT 21H
    OVER: 
    MOV AH,4CH
    INT 21H
CODE ENDS
END START