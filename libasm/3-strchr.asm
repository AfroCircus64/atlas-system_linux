BITS 64

section .text

; char *asm_strchr(const char *s, int c)
; {
;     while (*s != '\0')
;     {
;         if (*s == (char)c)
;         {
;             return ((char *)s);
;         }
;         s++;
;     }
;     if (c == '\0')
;     {
;         return ((char *)s);
;     }
;
;     return (NULL);
; }

global asm_strchr

asm_strchr:
    movzx rcx, sil

.search_loop:
    movzx rax, byte [rdi]
    cmp al, cl
    je .found
    test al, al
    jz .not_found
    inc rdi
    jmp .search_loop

.found:
    mov rax, rdi
    ret

.not_found:
    xor rax, rax
    ret
