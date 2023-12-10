#include "sabene.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _sabloadprogram(sdevice_t *device, sprogram_t raw)
{
    rom program;
    obram data;
    memcpy(program, data, DATA_SEGMENT_SIZE);
    raw += PROGRAM_SEGMENT_SIZE;
    memcpy(program, raw, PROGRAM_SEGMENT_SIZE);

    int i = 0;
    for(; i < strlen(raw) + 1; i++)
    {
        if(i % 16 == 0 && i != 0)
            printf("\n");

        printf("%02x ", raw[i]);
    }
    printf("\n");
}

sdevice_t *sabinit(sprogram_t program)
{
    sdevice_t *ret = (sdevice_t*)calloc(1, sizeof(sdevice_t));
    
    ret->addressLine = 0;
    ret->dataLine = 0;
    ret->cpu = cpuinit();
    ret->video = videoinit();

    memset(ret->rom, 0, PROGRAM_SEGMENT_SIZE);
    memset(ret->brom, 0, BOOT_SEGMENT_SIZE);
    memset(ret->disk, 0, DISK_SEGMENT_SIZE);
    memset(ret->obram, 0, DATA_SEGMENT_SIZE + STACK_SEGMENT_SIZE);

    _sabloadprogram(ret, program);

    return ret;
}

void sabclose(sdevice_t *device)
{
    videoclose(device->video);
    cpuclose(device->cpu);
    free(device);
}