section .text
	extern _ft_create_elem
	global _ft_list_push_front


_ft_list_push_front:
	push rbp
	mov rbp, rsp
	sub rsp, 0x10
	mov [rsp], rdi
	mov rdi, rsi
	call _ft_create_elem
	cmp rax, 0x0
	je _end
	mov rdi, [rsp]
	mov r8, [rdi]
	mov QWORD [rdi], rax
	mov [rax + 0x8], r8

_end:
	leave
	ret