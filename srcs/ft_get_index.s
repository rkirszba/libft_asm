section .text
	global _ft_get_index

_ft_get_index:
	push rbp
	mov rbp, rsp
	mov rax, -0x1
	and rsi, 0xff

_loop:
	inc rax
	cmp BYTE [rdi + rax], 0x0
	je _end_not_found
	xor	rdx, rdx
	mov dl, BYTE [rdi + rax]
	cmp rsi, rdx
	je _end
	jmp _loop

_end_not_found:
	mov rax, -0x1

_end:
	leave
	ret


