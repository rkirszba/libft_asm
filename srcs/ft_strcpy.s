section .text
	global _ft_strcpy

_ft_strcpy:
	push rbp
	mov rbp, rsp
	xor rcx, rcx

loop:
	cmp BYTE [rsi + rcx], 0x0
	je end
	mov al, [rsi + rcx]
	mov [rdi + rcx], al
	inc rcx
	jmp loop

end:
	mov al, [rsi + rcx]
	mov [rdi + rcx], al
	mov rax, rdi
	leave
	ret