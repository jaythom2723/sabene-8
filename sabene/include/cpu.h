#ifndef SABENE_CPU_H
#define SABENE_CPU_H

#include "defs.h"

/* general purpose register */
#define r0 0
/* general purpose register */
#define r1 1
/* general purpose register */
#define r2 2
/* general purpose register */
#define r3 3
/* general purpose register */
#define r4 4 
/* general purpose register */
#define r5 5
/* general purpose register */
#define r6 6
/* general purpose register */
#define r7 7
/* Flag Register */
#define r8 8
/* Overflow Register */
#define r9 9
/* Stack Pointer */
#define r10 10
/* Program Counter */
#define r11 11
/* Bus Interface Register */
#define bir 12

/* general purpose register */
#define f0 0
/* general purpose register */
#define f1 1
/* general purpose register */
#define f2 2
/* general purpose register */
#define f3 3

typedef enum bir_flags {
    RWRAM = 0b001,
    RROM,
    RWVRAM,
    RKEYBOARD,
    RWDISK,
    RWVGACOLORTABLE,
    RMOUSE
} sabenebirflag_t;

typedef enum flag_reg_flags {
    NONE     = 0b000000,
    NEGATIVE = 0b000001,
    CARRY    = 0b000010,
    OVERFLOW = 0b000100,
    EQUAL    = 0b001000,
    GREATER  = 0b010000,
    LESSER   = 0b100000,
} sabeneflagregflag_t;

typedef char reg;
typedef float regf;

typedef struct cpu {
    reg regs[13];
    regf fregs[4];
    reg *regPtr;                /* For internal stuff */
    regf *regfPtr;              /* For internal stuff */
    sabbool interrupt;
    sabbool running;
} sabcpu;

sabcpu *cpuinit(void);
void cpuclose(sabcpu *cpu);

#endif /* SABENE_CPU_H */