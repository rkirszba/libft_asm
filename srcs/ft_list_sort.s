section .text
	global _ft_list_sort



;	void ft_list_sort(t_list **begin_list, int (*cmp)());

;			stack
;
;	rsp			*begin_list
;	rsp + 0x8	cmp
;	rsp + 0x10	cursor


_ft_list_sort:
	push rbp
	mov rbp, rsp
	sub rsp, 0x20
	cmp rdi, 0x0				;	if begin_list == NULL		
	je _end						;		return
	mov r8, [rdi]				;	r8 = *begin_list = cursor
	cmp r8, 0x0					;	if cursor == NULL
	je _end						;		return
	mov [rsp], r8				;	
	mov [rsp + 0x8], rsi
	mov [rsp + 0x10], r8

_loop:
	mov r9, [r8 + 0x8]			;	r9 = cursor->next;
	cmp r9, 0x0					;	if cursor->next == NULL
	je _end						;		return
	mov rdi, [r8]				;	rdi = cursor->data
	mov rsi, [r9]				;	rsi = cursor->next->data
	call [rsp + 0x8]			;	call cmp function
	cmp eax, 0x0				;	if cmp > 0
	jg _swap					;	swap results + continue ;
	mov r8, [rsp + 0x10]		;	r8 = cursor
	mov r8, [r8 + 0x8]			;	r8 = cursor->next
	mov [rsp + 0x10], r8		;	cursor = cursor->next
	jmp _loop
	

_swap:
	mov r8, [rsp + 0x10]	;	r8 = cursor
	mov r9, [r8]			;	r9 = cursor->data
	mov r10, [r8 + 0x8]		; 	r10 = cursor->next
	mov r11, [r10]			;	r11 = cursor->next->data
	mov rdx, r9				;	rdx = tmp = cursor->data
	mov [r8], r11			;	cursor->data = cursor->next->data
	mov [r10], rdx			;	cursor->next->data = tmp
	mov r8, [rsp]			;	r8 = *begin_list
	mov [rsp + 0x10], r8	;	cursor = r8
	jmp _loop


_end:
	leave
	ret


