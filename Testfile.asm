section .data
	a db "Vishal kokane",10,0
	c db "Pune uNiversity",10,0
	First dd 10,20,30,40
	msg dd 50,90,87
	msg1 dd 50,90,870
	data1 dq 7,8,9,6,5,4
	dq 96,65,1,2,3
section .bss
	no1 resd 5
	no3 resb 10
	no2 resq 2
section .text
	extern printf
	global main
main:
	mov ecx,a
	mov eax,25
	xor ebx,ebx
	add edx,eax
	mov al,ah

