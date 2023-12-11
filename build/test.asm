thisisalabel:
label2:

; All of these work
pi:						DF 3.14
bruh4:					DB 5, 4, 2
bruh:					DB "Hello, World!", 13, 10, 0
bruh2:					DB "Hello, World!\n\0"
bruh3:					DB 'H'
word1:					DW 0xaa55
word2:					DW 0x5555, 0xaaaa, 0xffff
restest1:				RESB 2
restest2:				RESW 1
restest3:				RESF 1