#include <stdio.h>
#include <stdlib.h>

#include "sabene.h"

int main(void)
{
    rom program = {};

    sdevice_t *sab = sabinit(program);

    sabclose(sab);

    return 0;
}
