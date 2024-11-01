BITS 64

section .text

; size_t asm_strcspn(const char *s, const char *reject)
; {
;     size_t count = 0;
;     const char *r;
;
;     while (*s)
;     {
;         for (r = reject; *r; r++)
;         {
;             if (*s == *r)
;                 return (count);
;         }
;         count++;
;         s++;
;     }
;
;     return (count);
; }

global asm_strcspn

asm_strcspn:
	xor rax, rax

.loop_s:
	mov al, byte [rdi]
	test al, al
	jz .done
	mov rcx, rsi

.loop_r:
	mov dl, byte [rcx]
	test dl, dl
	jz .next_char
	cmp al, dl
	je .done
	inc rcx
	jmp .loop_r

.next_char:
	inc rdi
	inc rax
	jmp .loop_s

.done:
	ret
