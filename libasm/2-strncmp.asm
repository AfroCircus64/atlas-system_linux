BITS 64

section .text

; int asm_strncmp(const char *s1, const char *s2, size_t n)
;{
;     while (n > 0)
;     {
;         if (*s1 != *s2)
;         {
;             return (unsigned char)*s1 - (unsigned char)*s2;
;         }
;         if (*s1 == '\0')
;         {
;             break;
;         }
;         s1++;
;         s2++;
;         n--;
;     }
;     return 0;
; }

global asm_strncmp

asm_strncmp:
	test rdx, rdx
	jz .equal

.compare_loop:
	movzx rax, byte [rdi]
	movzx rbx, byte [rsi]
	cmp al, bl
	jne .not_equal
	test al, al
	jz .equal
	dec rdx
	jz .equal
	inc rdi
	inc rsi
	jmp .compare_loop

.not_equal:
	sub eax, ebx
	ret

.equal:
	xor eax, eax
	ret
