section .text
global asm_strlen

asm_strlen:
	; Save the base pointer
	push rbp

	; Move the string pointer to RSI
	mov rsi, rdi

	; Initialize RCX to 0 (will be used as counter)
	xor rcx, rcx

loop_str:
	; Compare the current byte with 0 (null terminator)
	cmp byte [rsi], 0

	; If it's 0, jump to the end of the loop
	je end_loop

	; Increment the counter
	inc rcx

	; Move to the next character
	inc rsi

	; Continue the loop
	jmp loop_str

end_loop:
	; Move the counter to RAX (return value)
	mov rax, rcx

	; Restore the base pointer
	pop rbp

	; Return from the function
	ret
