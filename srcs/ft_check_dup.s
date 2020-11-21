section .text
	global _ft_check_dup

_ft_check_dup:
	push rbp
	mov rbp, rsp
	xor rdx, rdx
	mov r8, -1
	
_loop:
	inc r8
	mov dl, BYTE[rdi + r8]
	cmp dl, 0x0
	je _end_no_dup
	mov r9, r8
	jmp _loop_loop

_loop_loop:
	inc r9
	cmp BYTE [rdi + r9], 0x0
	je _loop
	cmp dl, BYTE[rdi + r9]
	je _end_dup
	jmp _loop_loop

_end_no_dup:
	mov rax, 0x0
	leave
	ret

_end_dup:
	mov rax, 0x1
	leave
	ret

