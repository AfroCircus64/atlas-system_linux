BITS 64

section .text

; char *asm_strpbrk(const char *s, const char *accept)
; {
;     const char *a;
;
;     while (*s)
;     {
;         for (a = accept; *a; a++)
;         {
;             if (*s == *a)
;                 return ((char *)s);
;         }
;         s++;
;     }
;
;     return (NULL);
; }

global asm_strpbrk

asm_strpbrk:
    xor rax, rax

.loop_s:
    mov al, byte [rdi]
    test al, al
    jz .done
    mov rcx, rsi

.loop_a:
    mov dl, byte [rcx]
    test dl, dl
    jz .next_char
    cmp al, dl
    je .found
    inc rcx
    jmp .loop_a

.next_char:
    inc rdi
    jmp .loop_s

.found:
    mov rax, rdi
.done:
    ret
