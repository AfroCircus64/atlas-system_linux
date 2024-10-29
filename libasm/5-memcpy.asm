BITS 64

section .text

; void *asm_memcpy(void *dest, const void *src, size_t n)
; {
;     char *d = (char *)dest;
;     const char *s = (const char *)src;
;
;     while (n--)
;     {
;         *d++ = *s++;
;     }
;     return (dest);
; }

global asm_memcpy

asm_memcpy:
	mov rax, rdi
	test rdx, rdx
	jz .done

.copy_loop:
	movzx rcx, byte [rsi]
	mov [rdi], cl
	inc rsi
	inc rdi
	dec rdx
	jnz .copy_loop

.done:
	ret
