BITS 64

section .text

; size_t asm_puts(const char *str)
; {
; 	if (fputs(str, stdout) == EOF)
; 	{
; 		return (0);
; 	}
; 	if (putchar('\n') == EOF)
; 	{
; 		return (0);
; 	}
; 	return (strlen(str) + 1);
; }

global asm_puts

extern asm_strlen

asm_puts:
    call asm_strlen

    mov rcx, rax
    sub rsp, 8
    mov byte [rsp], 10
    mov rax, 1
    mov rdi, 1
    mov rsi, rdi
    mov rdx, rcx
    lea rdx, [rcx + 1]

    syscall

    add rsp, 8
    mov rax, rcx
    ret
