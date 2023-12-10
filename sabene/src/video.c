#include "gpu.h"

#include <stdlib.h>
#include <string.h>

sabvideo *videoinit(void)
{
    sabvideo *ret = calloc(1, sizeof(sabvideo));

    ret->cores[0] = cpuinit();
    ret->cores[1] = cpuinit();
    ret->corePtr = ret->cores;
    memset(ret->vram, 0, VIDEO_MEMORY_SEGMENT_SIZE + VGA_COLOR_SEGMENT_SIZE + VIDEO_DATA_SEGMENT_SIZE);

    return ret;
}

void videoclose(sabvideo *video)
{
    free(video->cores[0]);
    free(video->cores[1]);
    video->corePtr = NULL;
    free(video);
}