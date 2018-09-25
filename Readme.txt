


*I have written program of assembler that convert assembly program in
intermediate code through pass1 assembler
*the whole program divided into 3 parts
1)section data
2)section bss
3)section text
-->
first of all i have open the assembly file in read mode and fetch the record line by line till we reach to eof.
then record split into 3 groups

if any section found it gets validated and then enter into function 
1]section .data
in this section symbols,datatype,and data get separated and store into structure symtab

if 2nd entry dd,db,dq then data gets sorted accordingly into symbol table and data append into intermediate file

2] section .bss
if 2nd entry resd,resb,resq,resw then data gets sorted accordingly into symbol table and data append into intermediate file

3]section text
in this i separated opcode, oprand1, oprand2 and check for oprands in symtable and regtable and populate entries in ___.i file
separate out labels also
