BITS 64

section .text

; size_t asm_putc(int c)
; {
;     if (putchar(c) == EOF)
;     {
;         return (0);
;     }
;     return (1);
; }

global asm_putc

asm_putc:
    sub rsp, 8
    mov [rsp], dil
    mov rax, 1
    mov rdi, 1
    lea rsi, [rsp]
    mov rdx, 1

    syscall

    add rsp, 8

    mov rax, 1
    ret
