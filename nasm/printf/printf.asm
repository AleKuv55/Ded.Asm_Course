;My Printf

section .text

global start

start:
	
	push 0xff 
	mov rbp, rsp
	call Printf
	pop rax
	call Exit

;----------Procedures-----------;
;------------Printf-------------;
;-------------------------------;
;-------------------------------;
Printf:
	mov rsi, string		; rsi = &string - 1
cycle:
	dec rsi

	call Count
	cmp byte [rsi], '@'
	je gameover

	call Write
	add rsi, 1		;LOOK 

	call Do
	;add rsi, 2
	;cmp byte [rsi], '@'
	;je gameover
	
	;call Write
	;add rsi, 1 

	cmp byte [rsi], '@'
	jne cycle
	ret

gameover:
	call Write
	ret
;-------------------
;return number of symbols in rdx mov rsi to %
;------------------
Count:
	xor rdx, rdx
nextic:
 
	inc rsi
	inc rdx
	
	cmp byte [rsi], '@'	; if no more % it will stop the funct
	je finish
	
	cmp byte [rsi], '%'
	jne nextic
finish:
	ret
	
;------
;write
;return rsi in %
;------
Write:
	;dec rdx			;Errrr
	push rdx

	mov rax, 0x2000004	
	mov rdi, 1		; output
	sub rsi, rdx
	
	syscall

	pop rdx
	add rsi, rdx		; pointer in  %
	ret
;----
;do
;take rsi in %
;return in result transformed number rsi in %
;-----
Do:
	inc rsi			;after %
	cmp byte [rsi], 'b'
	je binary
	cmp byte [rsi], 'c'
	je cia
	cmp byte [rsi], 'd'
	je decimal
	cmp byte [rsi], 'h'
	je hex
	cmp byte [rsi], 'o'
	je octopus 
	cmp byte [rsi], 's'
	je prtstr
	jmp away
	
binary:
	call prtb
	jmp away
cia:	
	call prtc
	jmp away
decimal:
	call prtd
	jmp away
hex:
	call prth
	jmp away
octopus:
	call prto
	jmp away
prtstr:	
	call prts
	jmp away
away:
	;dec rsi			;again after  %Errrr
	ret

Exit: 
	mov rax, 0x2000001
	mov rdi, 0
	syscall

;-----translating procedurec----;
prtc:
	mov rax, [rbp]
	
	mov byte [rsi-1], al	; change % and 'c' 
	mov rdx, 1
	call Write
	;mov byte [rsi-1], 49
	ret
prtb:
	push rsi
	push rdx
	xor rdx, rdx
	mov rsi, result		;be careful
	mov r9 , 0x1000000000	;34 signs
	mov rax, [rbp]		;rax = input

next:
	mov r11, r9
	and r11, rax
	
	cmp r11, 0
	je zero
	jmp one	
zero:	
	shr r9, 1
	inc rsi
	jmp next		;escape first nulls
	 	
one:
	mov byte [rsi], 0x31
	inc rsi
	inc rdx
	shr r9, 1
	cmp r9, 0
	je aways
then:
	mov r11, r9
	and r11, rax
	cmp r11, 0
	jne one
zeror:
	mov byte [rsi], 0x30
	inc rsi
	inc rdx
	shr r9, 1
	cmp r9, 0
	jne then
aways:
	call Write
	pop rdx
	pop rsi
	ret
prth:
	ret
prto:
	ret
prtd:
	ret
prts:
	ret
;-------------------------------;	
section .data

string:	db "= %c @"
len:	equ $-string
result:	db "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
;curlen:dq  0

