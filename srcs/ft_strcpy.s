section .text
	global _ft_strcpy

_ft_strcpy:
	push rbp
	mov rbp, rsp
	xor rcx, rcx

_loop:
	cmp BYTE [rsi + rcx], 0x0
	je _end
	mov al, [rsi + rcx]
	mov [rdi + rcx], al
	inc rcx
	jmp _loop

_end:
	mov al, [rsi + rcx]
	mov [rdi + rcx], al
	mov rax, rdi
	leave
	ret