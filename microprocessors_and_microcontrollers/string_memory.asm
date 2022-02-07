; Sagar Paul 41
; 8086 program to display a string which is stored in the memory

ASSUME CS:CODE ,DS:DATA

DATA SEGMENT
    STR1 DB 'Hello World!$'
DATA ENDS

CODE SEGMENT
START:
    MOV AX,DATA
    MOV DS,AX
    LEA DX,STR1
    MOV AH,9H
    INT 21H
    MOV AH,4CH
    INT 21H
CODE ENDS
END START