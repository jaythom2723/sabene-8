#include "cpu.h"

#include <stdlib.h>

sabcpu *cpuinit(void)
{
    sabcpu *ret = calloc(1, sizeof(sabcpu));
    ret->regPtr = ret->regs;
    ret->regfPtr = ret->fregs;
    ret->interrupt = SAB_FALSE;
    ret->running = SAB_FALSE;
    return ret;
}

void cpuclose(sabcpu *cpu)
{
    free(cpu);
}