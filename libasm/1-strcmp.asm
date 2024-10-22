section .text
global asm_strcmp

asm_strcmp:
	; rdi = s1, rsi = s2
.loop:
	; Load byte from s1 into al
	mov al, [rdi]

	; Load byte from s2 into dl
	mov dl, [rsi]

	; Check if end of s1
	cmp al, 0
	je .end_of_str1

	; Check if end of s2
	cmp dl, 0
	je .end_of_str2

	; Compare the bytes
	cmp al, dl
	jl .less_than
	jg .greater_than

	; Move to next byte in s1
	inc rdi
	
	; Move to next byte in s2
	inc rsi
	
	; Repeat the loop
	jmp .loop

.end_of_str1:
	cmp dl, 0
	je .equal
	mov rax, -1
	ret

.end_of_str2:
	mov rax, 1
	ret

.less_than:
	mov rax, -1
	ret

.greater_than:
	mov rax, 1
	ret

.equal:
	xor rax, rax
	ret
