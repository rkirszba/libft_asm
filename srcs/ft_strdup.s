section .text
	extern _malloc
	extern _ft_strlen
	extern _ft_strcpy
	global _ft_strdup

_ft_strdup:
	push rbp
	mov rbp, rsp
	sub rsp, 0x10
	mov QWORD [rsp + 0x8], rdi
	call _ft_strlen
	inc rax
	mov rdi, rax
	call _malloc
	cmp rax, 0x0
	je _malloc_error
	mov rdi, rax
	mov rsi, QWORD [rsp + 0x8]
	call _ft_strcpy
	leave
	ret


_malloc_error:
	leave
	ret