%define MACH_SYSCALL(nb) 0x2000000 | nb
%define WRITE 4

section .text
	extern ___error
	global _ft_write

_ft_write:
	push rbp,
	mov rbp, rsp
	mov rax, MACH_SYSCALL(WRITE)
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