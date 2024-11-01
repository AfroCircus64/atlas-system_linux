BITS 64

section .text

; int asm_strncasecmp(const char *s1, const char *s2, size_t n)
; {
;     size_t i;
;
;     for (i = 0; i < n && s1[i] && s2[i]; i++)
;     {
;         int c1 = tolower((unsigned char)s1[i]);
;         int c2 = tolower((unsigned char)s2[i]);
;
;         if (c1 != c2)
;             return (c1 - c2);
;     }
;
;     if (i < n)
;     {
;         if (s1[i])
;             return (1);
;         if (s2[i])
;             return (-1);
;     }
;
;     return (0);
; }

global asm_strncasecmp

asm_strncasecmp:
    test rdx, rdx
    jz .return_zero

.compare_loop:
    movzx eax, byte [rdi]
    movzx ecx, byte [rsi]
    test  al, al
    jz .end_of_string
    test  cl, cl
    jz .end_of_string
    cmp al, 'A'
    jb .tolower1_end
    cmp al, 'Z'
    ja .tolower1_end
    add al, 32
.tolower1_end:
    movzx eax, al
    cmp cl, 'A'
    jb .tolower2_end
    cmp cl, 'Z'
    ja .tolower2_end
    add cl, 32
.tolower2_end:
    movzx ecx, cl
    cmp eax, ecx
    jne .return_difference
    inc rdi
    inc rsi
    dec rdx
    jnz .compare_loop

.return_zero:
    xor eax, eax
    ret

.return_difference:
    sub eax, ecx
    ret

.end_of_string:
    test al, al
    jz .check_second_string
    test cl, cl
    jz .return_difference
    xor eax, eax
    ret

.check_second_string:
    test cl, cl
    jz .return_zero
    sub eax, ecx
    ret
