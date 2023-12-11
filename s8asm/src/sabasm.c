#include "sabasm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int getnamelength(char *line);
static void processline(label_t *label, char *line);

static unsigned short createdlabel(label_t *label, char *line);

static unsigned char checkfordirective(char *line);
static unsigned char checkforlabel(char *line);

static unsigned short dataptr = 0;                 /* The current byte in data memory (helps with label declaration) */
static label_t *labelsptr = 0;
static token_t *tokensptr = 0;

void init(program_t *program)
{
    dataptr = 0;
    labelsptr = program->labels;
    tokensptr = program->tokens;
}

void lex(char *const src, program_t *program)
{
    labelpass(src, program);
    secondpass(src, program);
}

void labelpass(char *const src, program_t *program)
{
    char *line = strtok(src, "\n");
    label_t *label = calloc(1, sizeof(label_t));

    while(line != NULL)
    {
        if(checkfordirective(line))
        {
            /* a directive has been found, reserve memory and modify data pointer */
            int step = createdlabel(label, line);

            dataptr += step;
        }

        line = strtok(NULL, "\n");
    }
}

void secondpass(char *const src, program_t *program)
{
    
}







/* STATIC FUNCTION DEFS */
int getnamelength(char *line)
{
    int count = 0;

    while(!(WHITESPACE_CHARACTER_CHECK(*line) || *line == ':'))     /* check for a space,newline,cr,null,colon,tab */
    {
        line ++;
        count ++;
    }

    line -= count;                                  /* make sure we reset the pointer */

    return count;
}

void processline(label_t *label, char *line)
{
    int namelen = getnamelength(line);

    char buf[namelen]; /* temporary name buffer */
    int i = 0;
    for(; i < namelen; i++)
    {
        buf[i] = line[i];
    }
    buf[namelen] = 0;

    label->name = calloc(namelen, sizeof(char));
    strcpy(label->name, buf);
}


unsigned short createdlabel(label_t *label, char *line) /* returns the step for the data ptr */
{
    processline(label, line);

    if (label->name != NULL)
        printf("%s\n", label->name);

    return 0;
}

unsigned char checkfordirective(char *line)
{
    int i = 0;
    char *dir = NULL;

    for(; i < NUM_DIRECTIVES; i++)
    {
        dir = strstr(line, directives[i]); /* check if the line contains a valid directive */
        if(dir != NULL)
            return 1;
    }

    return 0;
}