BITS 64

section .text

; size_t asm_strspn(const char *s, const char *accept)
; {
;     size_t count = 0;
;     const char *a;
;
;     while (*s)
;     {
;         for (a = accept; *a; a++)
;         {
;             if (*s == *a)
;                 break;
;         }
;         if (*a == '\0')
;         {
;             break;
;         }
;         count++;
;         s++;
;     }
;
;     return (count);
; }

global asm_strspn

asm_strspn:
	xor rax, rax
	mov rcx, rdi
	jmp .loop_start

.loop_start:
	cmp byte [rcx], 0
	je .end
	mov rsi, rdx
	jmp .inner_loop

.inner_loop:
	cmp byte [rsi], 0
	je .increment_s
	mov al, [rcx]
	cmp al, [rsi]
	je .increment_count
	inc rsi
	jmp .inner_loop

.increment_count:
	inc rax
	inc rcx
	jmp .loop_start

.increment_s:
	inc rcx
	jmp .loop_start

.end:
	ret
