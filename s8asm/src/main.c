#include "sabasm.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>

char *const 
get_source(char *path)
{
    FILE *file = fopen(path, "r");
    if(file == NULL)
        return NULL;

    fseek(file, 0l, SEEK_END);
    size_t size = ftell(file) + 1;
    rewind(file);

    char *const src = calloc(size, sizeof(char));
    fread(src, 1, size, file);
    if(src == NULL)
        return NULL;

    return src;
}

int 
main(int argc, char **argv)
{
    argc--;
    argv++;
    
    char *const src = get_source(*argv);
    if(src == NULL)
        errx(-1, "Source could not be found!");

    program_t *program = (program_t *) calloc(1, sizeof(program_t));
    lex(src, program);

    free(program);
    free(src);

    return 0;
}