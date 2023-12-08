#ifndef SABENE_H
#define SABENE_H

#include "defs.h"

#include "cpu.h"
#include "mem.h"

typedef struct sabene {
    unsigned short addressLine;
    char dataLine;
    sabcpu *cpu;
    obram ram;
    const rom rom;
} sdevice_t;

sdevice_t *sabinit(rom program);
void sabclose(sdevice_t *device);

#endif /* SABENE_H */