section .text
	global _ft_list_sort


_ft_list_sort:
	push rbp
	mov rbp, rsp
	sub rsp, 0x20
	cmp rdi, 0x0
	je _end
	mov r8, [rdi]
	mov QWORD [rsp], r8
	mov QWORD [rsp + 0x8], rsi
	mov QWORD [rsp + 0x10], r8

_loop:
	mov r9, [r8 + 0x8]
	cmp r9, 0x0
	je _end
	mov rdi, [r8]
	mov rsi, [r9]
	mov r10, [rsp + 0x8]
	call r10
	cmp rax, 0x0
	jg _swap
	mov r8, [rsp + 0x10]
	mov r8, [r8 + 0x8]
	mov QWORD [rsp + 0x10], r8
	jmp _loop
	

_swap:
	mov r8, [rsp + 0x10]    ; curseur
	mov r9, [r8]			; data du curseur
	mov r10, [r8 + 0x8]		; curseur ->next
	mov r11, [r10]			; data de curseur->next
	mov rdx, r9				; tmp
	mov [r8], r11
	mov [r10], rdx
	mov r8, [rsp]
	mov [rsp + 0x10], r8
	jmp _loop


_end:
	leave
	ret


