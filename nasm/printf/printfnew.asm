;My Printf
; to call from C nasm -f macho64 printfnew.asm && gcc -c main.c && gcc -Wl,-no_pie main.o printfnew.o -o a.out  
; ./a.out
section .text

global _printfnew

_printfnew:
	;mov rdi, ex	
	;push rdi
	;push 0xeda
	;push 10
	;push 70
	
	pop rbx		; for C  printf pushes
	push r9
	push r8
	push rcx
	push rdx
	push rsi
	push rdi
	push rbx	; for C 

	mov rbp, rsp
	add rbp, 16

	call Printf
	call Exit

;----------Procedures-----------;
;------------Printf-------------;
;-------------------------------;
;-------------------------------;
Printf:
	;mov rsi, string		; rsi = &string - 1
	mov rsi, rdi		; for C printf
cycle:
	dec rsi
	xor rdx, rdx

	call Count
	cmp byte [rsi], '@'
	je gameover
	dec rsi
	dec rdx			; before %
	
	call Write		; output everything before %

	call Do

	cmp byte [rsi], '@'
	jne cycle
	ret
gameover:
	call Write
	ret
;------------------------------;
;Count:
;return number of symbols
; in rdx mov rsi to %
;------------------------------;
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
;------------------------------;
;Write
;return rsi in %
;------------------------------;
Write:
	push rdx

	mov rax, 0x2000004	
	mov rdi, 1		; output
	sub rsi, rdx
	
	syscall

	pop rdx
	add rsi, rdx		; pointer in  %
	ret
;------------------------------;
;Do
;take rsi in %
;return in result
;transformed number rsi in %
;------------------------------;
Do:
	add rsi, 2		; after %
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
	cmp byte [rsi], '%'
	je prtperc
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
prtperc:
	call prtp
	jmp away
away:
	add rsi, 2		; after % argument Attentionnnnnnnnnn
	add rbp, 8
	ret

;-----translating procedurec----;
prtp:
	push rsi
	push rdx
	
	mov rsi, result
	mov byte [rsi], '%' 	; change % and 'c' 

	mov rdx, 1
	inc rsi

	call Write

	pop rdx
	pop rsi
	ret

;	prtc = printf %c        ;
;	destroy rax, rdx	;

prtc:
	push rsi
	push rdx
	
	mov rax, [rbp]
	mov rsi, result
	mov byte [rsi], al	; change % and 'c' 

	mov rdx, 1
	inc rsi

	call Write

	pop rdx
	pop rsi
	ret
;-------------------------------;
prtb:
	push rsi
	push rdx
	xor rdx, rdx
	mov rsi, result		;be careful
	mov r9 , 0x10000000	;32 signs
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
	;inc rsi
	ret
;-------------------------------;
prth:	
	push rsi
	push rdx
	xor rdx, rdx
	mov rsi, result		;be careful
	
	mov r9 , 0xf0000000	;32 signs
	mov rax, [rbp]		;rax = input
	
	mov rcx, 28		;offset

.next:
	mov r11, r9
	and r11, rax
	shr r11, cl
	sub cl, 4

	cmp r11, 0
	je .zero

	jmp .one	
.zero:	
	shr r9, 4
	inc rsi
	jmp .next		;escape first nulls
	 	
.one:
	cmp r11, 9
	jna .here
	add r11, 0x27
	mov rbx, r11
	mov byte [rsi], bl	; look
.here:
	add r11, 0x30
	mov rbx, r11
	mov byte [rsi], bl	; look

	inc rsi
	inc rdx
	shr r9, 4
	cmp r9, 0
	je .aways
.then:
	mov r11, r9
	and r11, rax
	shr r11, cl
	sub cl, 4
	cmp r11, 0
	jne .one
.zeror:
	mov byte [rsi], 0x30
	inc rsi
	inc rdx
	shr r9, 4
	cmp r9, 0
	jne .then
.aways:
	
	call Write
	pop rdx
	pop rsi
	;inc rsi
	ret	
;-------------------------------;
prto:
	push rsi
	push rdx
	xor rdx, rdx
	mov rsi, result		;be careful
	
	mov r9 , 0x38000000	;32 signs
	mov rax, [rbp]		;rax = input
	
	mov rcx, 27		;offset

.next:
	mov r11, r9
	and r11, rax
	shr r11, cl
	sub cl, 3

	cmp r11, 0
	je .zero

	jmp .one	
.zero:	
	shr r9, 3
	inc rsi
	jmp .next		;escape first nulls
	 	
.one:

	add r11, 0x30
	mov rbx, r11
	mov byte [rsi], bl	; look

	inc rsi
	inc rdx
	shr r9, 3
	cmp r9, 0
	je .aways
.then:
	mov r11, r9
	and r11, rax
	shr r11, cl
	sub cl, 3
	cmp r11, 0
	jne .one
.zeror:
	mov byte [rsi], 0x30
	inc rsi
	inc rdx
	shr r9, 3
	cmp r9, 0
	jne .then
.aways:
	
	call Write
	pop rdx
	pop rsi
	;inc rsi
	ret
;-------------------------------;
prtd:
	push rsi	
	push rdx
	
	;xor rdx, rdx
	xor r12, r12		;counter
	mov rsi, result		; rsi buffer
	add rsi, lenres		; at the end of buffer
	;sub rsi, len		;reeeeeerrrroreo!!!
	mov rax, [rbp]		; preparing rda = valuable
	mov rcx, 10		
.next:
	xor rdx, rdx
	div rcx
	add rdx, 0x30
	mov byte [rsi], dl
	dec rsi
	inc r12
	cmp rax, 0
	ja .next
	
	;inc r12
	mov rdx, r12		; for write

	inc rsi	
	add rsi, rdx
	call Write
	
	pop rdx
	pop rsi
	;add rsi, 1
	ret
;-------------------------------;
prts:
	push rdx
	push rsi	
	xor rdx, rdx		; counter of str chars
	mov rsi, [rbp]		; get str addr
	;sub rsi, lenres
	;sub rsi, len 
.next:
	cmp byte [rsi], 0 	; look for end of str
	je .contin

	inc rsi
	inc rdx
	jmp .next

.contin:	
	;dec rsi
	;dec rdx
	call Write
	pop rsi
	pop rdx
	;dec rsi
	ret
;-------------------------------;
Exit: 
	mov rax, 0x2000001
	mov rdi, 0
	syscall

;-------------------------------;	
section .data

string:	db " %s @"
len:	equ $-string
result:	db "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
lenres: equ $-result
ex:	db "it0ifffffffffffffffffffffffffffffffffffffffffffffis@"
;curlen:dq  0
	
