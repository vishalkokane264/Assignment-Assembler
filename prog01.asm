section .data			
	First db "First string",10,0
	Second db "Second string",10,0
	F_len db 13

section .bss
	Third resb F_len
	Fourth resb S_len
section .text
global main
	extern printf
main:
	mov esi, First
	mov edi, Second
	mov ecx, F_len
	movsb
	push Third
	call printf
	add esp,4 
