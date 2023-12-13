#ifndef S8ASM_DEFS_H
#define S8ASM_DEFS_H

#define BOOT_SEGMENT_BASE                       0x0000
#define BOOT_SEGMENT_LIMIT                      0x0200

#define DATA_SEGMENT_BASE                       0x0201
#define DATA_SEGMENT_LIMIT                      0x0FFF

#define PROGRAM_SEGMENT_BASE                    0x1000
#define PROGRAM_SEGMENT_LIMIT                   0x1FFF

#define VIDEO_MEMORY_SEGMENT_BASE               0x2000
#define VIDEO_MEMORY_SEGMENT_LIMIT              0x6B00

#define DISK_SEGMENT_BASE                       0x6B01
#define DISK_SEGMENT_LIMIT                      0x7B00

#define STACK_SEGMENT_BASE                      0x7B01
#define STACK_SEGMENT_LIMIT                     0x8B00

#define VGA_COLOR_SEGMENT_BASE                  0x8B01
#define VGA_COLOR_SEGMENT_LIMIT                 0xD601

#define VIDEO_DATA_SEGMENT_BASE                 0xD602
#define VIDEO_DATA_SEGMENT_LIMIT                0xE602

#define FREE_SEGMENT_BASE                       0xE603
#define FREE_SEGMENT_LIMIT                      0xFFFF

#define BOOT_SEGMENT_SIZE                       (BOOT_SEGMENT_LIMIT - BOOT_SEGMENT_BASE)
#define DATA_SEGMENT_SIZE                       (DATA_SEGMENT_LIMIT - DATA_SEGMENT_BASE)
#define PROGRAM_SEGMENT_SIZE                    (PROGRAM_SEGMENT_LIMIT - PROGRAM_SEGMENT_BASE)
#define VIDEO_MEMORY_SEGMENT_SIZE               (VIDEO_MEMORY_SEGMENT_LIMIT - VIDEO_MEMORY_SEGMENT_BASE)
#define DISK_SEGMENT_SIZE                       (DISK_SEGMENT_LIMIT - DISK_SEGMENT_BASE)
#define STACK_SEGMENT_SIZE                      (STACK_SEGMENT_LIMIT - STACK_SEGMENT_BASE)
#define VGA_COLOR_SEGMENT_SIZE                  (VGA_COLOR_SEGMENT_LIMIT - VGA_COLOR_SEGMENT_BASE)
#define VIDEO_DATA_SEGMENT_SIZE                 (VIDEO_DATA_SEGMENT_LIMIT - VIDEO_DATA_SEGMENT_BASE)
#define FREE_SEGMENT_SIZE                       (FREE_SEGMENT_LIMIT - FREE_SEGMENT_BASE)

#define END_CHARACTERS(chr)                     chr == '\n' || chr == '\0' || chr == 13
#define WHITESPACE_CHARACTER_CHECK(chr)         chr == ' ' || chr == '\n' || chr == '\0' || chr == 13 || chr == '\t'
#define IS_NUMBER(chr)                          chr == '1' || chr == '2' || chr == '3' || chr == '4' || chr == '5' || chr == '6' || chr == '7' || chr == '8' || chr == '9' || chr == '0'
#define IS_HEX(str, lastchr)                    *(str + 1) == 'x' || str[lastchr - 1] == 'h'
#define IS_BIN(str)                             *(str + 1) == 'b'

#define NUM_DIRECTIVES                          7

#define DB                                      0
#define DW                                      1
#define DF                                      2
#define RESB                                    3
#define RESW                                    4
#define RESF                                    5
#define EQU                                     6

static const char *const directives[] = {
    "DB", "DW", "DF", "RESB", "RESW", "RESF", "EQU"
};

static const char *const instructions[] = {
    "MOV", "STR", "RD", /* moving data into/out of reigster/memory */
    "ADD", "SUB", "DIV", "MUL", "AND", "XOR", "OR", "CMP", /* ALU instructions */ 
    "JMP", "JEQ", "JNQ", "JC", "JNC", "JL", "JNL", "JLE", "JNLE", "JG", "JNG", "JGE", "JNGE", /* modify program counter directly */
    "INT", /* call a kernel-specific pre-built function. */
    "PUSH", "POP", /* push/pop a value to/from stack (first in last out) */
    "CALL", "RET", /* modify the program counter briefly, make sure to store the program counter to the stack */
    "HLT", /* stop all cpu function */
    "BIR", /* modify the bus interface register */
    "INC", "DEC", /* increment/decrement address,register,value */
    "PUSHA", /* push all register values to the stack */
    "CALLZ", "CALLNZ", "CALLC", "CALLNC", "CALLL", "CALLNL", "CALLLE", "CALLNLE", "CALLG", "CALLNG", "CALLGE", "CALLNGE", /* conditional call */
    "CMVZ", "CMVNZ", "CMVC", "CMVNC", "CMVL", "CMVNL", "CMVLE", "CMVNLE", "CMVG", "CMVNG", "CMVGE", "CMVNGE", /* conditional moving */
};

typedef enum token_type
{
    IDENTIFIER, INSTRUCTION, SEPARATOR, PUNCTUATOR, OPERATOR, LITERAL,
    COMMENT, KEYWORD
} token_type_t;

typedef struct token 
{
    unsigned char ttype; /* Token Type */
    char *value; /* Value of the token */
} token_t;

typedef struct label
{
    unsigned short address;
    char *name;
    char *value;
    unsigned char directive;
} label_t;

typedef struct program 
{
    token_t tokens[255]; /* max 255 tokens (expand later) */
    label_t *labels[255]; /* max 255 labels (expand later) */
    char byteCode[DATA_SEGMENT_SIZE + PROGRAM_SEGMENT_SIZE];
} program_t;

#endif /* DEFS_H */