section .text
	extern _malloc
	global _ft_create_elem

_ft_create_elem:
	push rbp
	mov rbp, rsp
	sub rsp, 0x10
	mov QWORD [rsp], rdi
	mov rdi, 0x10
	call _malloc
	cmp rax, 0x0
	je _end
	mov QWORD [rax + 0x8], 0x0;
	mov r8, QWORD [rsp]
	mov [rax], r8

_end:
	leave
	ret
