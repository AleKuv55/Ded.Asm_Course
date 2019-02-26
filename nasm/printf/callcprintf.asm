; nasm -f macho64 callcprintf.asm -o call.o
; gcc -lc -Wl,-no_pie call.o
; ./a.out 
extern _printf

global _main

section .text

_main:
	push rbp
	
	mov rdi, string
	;mov rsi, 10
	;mov rdx, 0xeda
	xor rax, rax
	
	call _printf
	
	pop rbp
	ret
section .data

string:	db " ergrdh", 10, 0
