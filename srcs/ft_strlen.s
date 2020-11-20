section .text
	global _ft_strlen

_ft_strlen:
	push rbp			
    mov rbp, rsp						
    xor rax, rax		

_loop:
    cmp BYTE [rdi + rax], 0x0				
    je _end
	inc rax
	jmp _loop

_end:
	leave
	ret
