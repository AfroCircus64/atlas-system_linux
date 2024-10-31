BITS 64

section .text

global asm_strcasecmp

asm_strcasecmp:
    xor rax, rax

.loop:
    mov al, byte [rdi]
    mov bl, byte [rsi]
    test al, al
    je .check_end
    test bl, bl
    je .check_end
    cmp al, 'A'
    jl .lower_check_bl
    cmp al, 'Z'
    jg .lower_check_bl
    add al, 32

.lower_check_bl:
    cmp bl, 'A'
    jl .compare
    cmp bl, 'Z'
    jg .compare
    add bl, 32

.compare:
    cmp al, bl
    jne .done
    inc rdi
    inc rsi
    jmp .loop

.check_end:
    test al, al
    jne .lesser
    test bl, bl
    jne .greater
    jmp .equal

.done:
    cmp al, bl
    ja .greater
    jb .lesser

.equal:
    xor rax, rax
    ret

.greater:
    mov rax, 1
    ret

.lesser:
    mov rax, -1
    ret
