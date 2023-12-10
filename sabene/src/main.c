#include <stdio.h>
#include <stdlib.h>

#include "sabene.h"

int main(void)
{
    sprogram_t program = {};

    sdevice_t *sab = sabinit(program);

    sabclose(sab);

    return 0;
}
