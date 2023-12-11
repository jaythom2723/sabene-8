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
    init(program);
    lex(src, program);


    /* destroy existing labels */
    int i = 0;
    int j = 0;
    for(; i < 255; i++)
    {
        if(program->labels[i] == NULL)
            break;

        if(program->labels[i]->value != NULL)
        {
            for(j=0; j < sizeof(program->labels[i]->value); j++)
            {
                if(program->labels[i]->value[j] == 0)
                    break;

                printf("%02x ", (unsigned char) (program->labels[i]->value[j]));
            }
            printf("\n");
        }

        free(program->labels[i]->name);
        free(program->labels[i]->value); /* TODO: remember, we can't always assume value is allocated, remember to check for its existence first before freeing */
        free(program->labels[i]);
    }

    free(program);
    free(src);

    return 0;
}