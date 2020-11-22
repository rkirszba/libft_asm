section .text
	extern _free
	global _ft_list_remove_if

;	void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(),
;	void (*free_fct)(void *))


;			stack
;
;	rsp			begin_list
;	rsp + 0x8	data_ref
;	rsp + 0x10	cmp
;	rsp + 0x18	free_fct
;	rsp + 0x20	prev_cursor
;	rsp + 0x28	cursor
;	rsp + 0x30	tmp
;


_ft_list_remove_if:
	push rbp,
	mov rbp, rsp
	sub rsp, 0x40
	mov [rsp], rdi				
	mov [rsp + 0x8], rsi
	mov [rsp + 0x10], rdx
	mov [rsp + 0x18], rcx
	mov QWORD [rsp + 0x20], 0x0
	mov r8, [rdi]
	mov [rsp + 0x28], r8

_loop:
	cmp r8, 0x0					; if curs == NULL
	je _end						;	return
	mov rdi, [r8]				; rdi = curs->data
	mov rsi, [rsp + 0x8]		; rsi = data_ref
	call [rsp + 0x10]			; call cmp
	cmp eax, 0x0				; if cmp == 0
	je _delete_node				; 	_delete_node
	mov r8, [rsp + 0x28]		; r8 == cursor
	mov [rsp + 0x20], r8		; prev_cursor = cursor
	mov r8, [r8 + 0x8]			; r8 = cursor->next
	mov [rsp + 0x28], r8		; cursor = cursor->next
	jmp _loop
	


_delete_node:
	mov r8, [rsp + 0x28]		; r8 = cursor
	mov [rsp + 0x30], r8		; tmp = cursor
	cmp QWORD [rsp + 0x20], 0x0	; if prev_cursor == NULL
	je _case_first_node			; 	case_first_node
	jne _case_not_first_node


_case_first_node:
	mov r8, [rsp]				; r8 = begin_list
	mov r9, [r8]				; r9 = *begin_list
	mov r9, [r9 + 0x8]			; r9 = (*begin_list)->next
	mov [r8], r9				; *begin_list = (*begin_list)->next
	mov r8, r9
	jmp _end_delete_node		; 

_case_not_first_node:
	mov r8, [rsp + 0x28]		; r8 = curs
	mov r8, [r8 + 0x8]			; r8 = curs->next  
	mov r9, [rsp + 0x20]		; r9 = prev_cur
	mov [r9 + 0x8], r8			; prev_curs = curs->next
	jmp _end_delete_node


_end_delete_node:
	mov [rsp + 0x28], r8        ; curs = curs->next
	mov r8, [rsp + 0x30]		; r8 = tmp
	mov rdi, [r8]				; rdi = tmp->data
	call [rsp + 0x18]			; free(tmp->data)
	mov rdi, [rsp + 0x30]		; rdi = tmp
	call _free					; free(tmp)
	mov r8, [rsp + 0x28]		; r8 = curs
	jmp _loop				



_end:
	leave
	ret

