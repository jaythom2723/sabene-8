thisisalabel:
label2:

; All of these generate errors
testlabel:				DF
another_label:			RESB
thisisalabelaswell      DB
woop_woop               RESW

; All of these work
pi:						DF 3.14
bruh:					DB "Hello, World!", 13, 10, 0
bruh2:					DB "Hello, World!\n\0"
bruh3:					DB 'H'
word1:					DW 0xaa55
restest1:				RESB 2
restest2:				RESW 1
restest3:				RESF 1