section .text
	global _ft_strcmp

_ft_strcmp:
	push rbp
	mov rbp, rsp
	xor rax, rax
	xor rcx, rcx
	xor rdx, rdx

_loop:
	mov al, BYTE [rsi + rcx]
	cmp BYTE [rdi + rcx], al
	jne _end_diff
	cmp BYTE [rdi + rcx], 0X0
	je _end_same
	inc rcx
	jmp _loop

_end_diff:
	mov al, BYTE [rdi + rcx]
	mov dl, BYTE [rsi + rcx]
	sub eax, edx
	leave
	ret

_end_same:
	mov al, 0x0
	leave
	ret

