#include "sabene.h"

#include <stdlib.h>
#include <string.h>

sdevice_t *sabinit(rom program)
{
    sdevice_t *ret = (sdevice_t*)calloc(1, sizeof(sdevice_t));
    
    ret->addressLine = 0;
    ret->dataLine = 0;
    ret->cpu = cpuinit();

    memcpy(ret->rom, program, sizeof(ret->rom));

    return ret;
}

void sabclose(sdevice_t *device)
{
    cpuclose(device->cpu);
    free(device);
}