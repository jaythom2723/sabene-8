thisisalabel:
label2:

; All of these work
rah: 					DB 0x48, 0xe
pi:						DF 3.14
bruh4:					DB 5, 4, 2
bruh:					DB "Hello, World!", 13, 10, 0
bruh2:					DB "Hello, World!\n\0"
bruh3:					DB 'H'
rahhh:					DB 0x48
word1:					DW 0xaa55
word2:					DW 0x5555, 0xaaaa, 0xffff
word3:					DW 0b1110010111001110
word3:					DW 0b1110010111001110, 0b1111110111001110
word4:					DW 0b0000000010000000
word5:					DW 0b0000010011000011
restest1:				RESB 2
restest2:				RESW 1
restest3:				RESF 1