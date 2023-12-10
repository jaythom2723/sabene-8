#ifndef SAB_GPU_H
#define SAB_GPU_H

#include "cpu.h"
#include "mem.h"

typedef struct {
    sabcpu *cores[2];
    sabcpu **corePtr;
    vram vram;
} sabvideo;

sabvideo *videoinit(void);
void videoclose(sabvideo *video);

#endif /* SAB_GPU_H */