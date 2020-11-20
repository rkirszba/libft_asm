%define MACH_SYSCALL(nb) 0x2000000 | nb
%define READ 3

section .text
	extern ___error
	global _ft_read

_ft_read:
	push rbp
	mov rbp, rsp
	mov rax, MACH_SYSCALL(READ)
	syscall
	jc _error
	leave
	ret

_error:
	mov r8, rax
	call ___error
	mov [rax], r8
	mov rax, -1
	leave
	ret