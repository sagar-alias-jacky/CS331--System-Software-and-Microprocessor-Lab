; Sagar Paul 41
; 8086 program to print Hello World!

assume cs:code, ds:data

data segment
    s1 db 'Hello World!$'
data ends

code segment
start:
    mov ax,data
    mov ds,ax

    lea dx,s1
    mov ah,9
    int 21h

    mov ah,4ch
    int 21h
code ends
end start
