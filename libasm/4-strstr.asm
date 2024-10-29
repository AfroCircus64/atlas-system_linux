BITS 64

section .text

; char *asm_strstr(const char *haystack, const char *needle)
; {
;     if (*needle == '\0')
;     {
;         return ((char *)haystack);
;     }
;     for (; *haystack != '\0'; haystack++)
;     {
;         const char *h = haystack;
;         const char *n = needle;
;
;         while (*h == *n && *n != '\0')
;         {
;             h++;
;             n++;
;         }
;         if (*n == '\0')
;         {
;             return ((char *)haystack);
;         }
;     }
;
;
;     return (NULL);
; }

global asm_strstr

asm_strstr:
    movzx rcx, byte [rsi]
    test rcx, rcx
    jz .return_haystack

.next_haystack_char:
    movzx rax, byte [rdi]
    test rax, rax
    jz .not_found
    mov rbx, rdi
    mov rdx, rsi

.compare_loop:
    movzx rax, byte [rbx]
    movzx rcx, byte [rdx]
    cmp rax, rcx
    jne .advance_haystack
    test rcx, rcx
    jz .found
    inc rbx
    inc rdx
    jmp .compare_loop

.advance_haystack:
    inc rdi
    jmp .next_haystack_char

.found:
    mov rax, rdi
    ret

.not_found:
    xor rax, rax
    ret

.return_haystack:
    mov rax, rdi
    ret
