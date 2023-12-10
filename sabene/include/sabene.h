#ifndef SABENE_H
#define SABENE_H

#include "defs.h"

#include "cpu.h"
#include "mem.h"
#include "gpu.h"

typedef struct sabene {
    unsigned short addressLine;
    char dataLine;
    sabcpu *cpu;
    sabvideo *video;

    bootrom brom;
    disk disk;
    obram obram;
    rom rom;
} sdevice_t;

sdevice_t *sabinit(sprogram_t program);
void sabclose(sdevice_t *device);

#endif /* SABENE_H */