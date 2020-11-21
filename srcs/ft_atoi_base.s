section .text
	extern _ft_strlen
	extern _ft_check_dup
	extern _ft_get_index
	global _ft_atoi_base


_check_no_invalid:
	cmp dl, 0x2b
	je _input_error
	cmp dl, 0x2d
	je _input_error
	cmp dl, 0x20
	je _input_error
	cmp dl, 0x9
	je _input_error
	cmp dl, 0xa
	je _input_error
	cmp dl, 0xb
	je _input_error
	cmp dl, 0xc
	je _input_error
	cmp dl, 0xd
	je _input_error
	jmp _loop1

_neg:
	mov DWORD [rsp + 0x1c], -0x1
	inc QWORD [rsp]
	jmp _compute_nb

_pos:
	inc QWORD [rsp]
	jmp _compute_nb



;	rsp			= str
;	rsp + 0x8	= base
;	rsp + 0x10	= base len
;	rsp + 0x18  = final nb
;	rsp + 0x1c  = sign


_ft_atoi_base:

	push rbp
	mov rbp, rsp

	sub rsp, 0x20
	mov [rsp], rdi
	mov [rsp + 0x8], rsi
	mov rdi, QWORD [rsp + 0x8]

	call _ft_strlen
	cmp rax, 0x0
	je _input_error
	cmp rax, 0x1
	je _input_error
	mov [rsp + 0x10], rax

	call _ft_check_dup
	cmp rax, 0x1
	je _input_error

	mov rcx, -0x1
	mov rsi, QWORD [rsp + 0x8]


_loop1:
	inc rcx
	cmp BYTE [rsi + rcx], 0x0
	je _get_sign
	mov dl, [rsi + rcx]
	jmp _check_no_invalid


_get_sign:
	mov DWORD [rsp + 0x1c], 0x1
	mov rdx, QWORD [rsp]
	cmp BYTE [rdx], 0x2d
	je _neg
	cmp BYTE [rdx], 0x2b
	je _pos

_compute_nb:
	mov DWORD [rsp + 0x18], 0x0
	dec QWORD [rsp]

_loop2:
	inc QWORD [rsp]
	mov rdx, QWORD [rsp]
	cmp BYTE [rdx], 0x0
	je _end
	mov rdi, [rsp + 0x8]
	xor rsi, rsi
	mov rsi, [rdx]
	and rsi, 0xff
	call _ft_get_index
	cmp eax, -0x1
	je _input_error
	xor rdx, rdx
	mov edx, [rsp + 0x18]
	imul rdx, [rsp + 0x10]
	add rdx, rax
	mov [rsp + 0x18], edx
	jmp _loop2

_end:
	mov rax, [rsp + 0x18]
	imul rax, [rsp + 0x1c]
	leave
	ret


_input_error:
	mov rax, 0
	leave
	ret