section .text
	global _ft_list_size


_ft_list_size:
	push rbp
	mov rbp, rsp
	mov rax, -0x1

_loop:
	inc rax
	cmp rdi, 0x0
	je _end
	mov r8, [rdi + 0x8]
	mov rdi, r8
	jmp _loop

_end:
	leave
	ret