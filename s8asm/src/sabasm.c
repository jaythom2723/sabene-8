#include "sabasm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int getnamelength(char *line);
static char *getname(int namelen, char *line);
static void processline(label_t *label, char *line);

static unsigned short createdlabel(label_t *label, char *line);

static unsigned char checkfordirective(label_t *label, char *line);
static unsigned char checkforlabel(char *line);

static unsigned short dataptr = 0;                 /* The current byte in data memory (helps with label declaration) */
static label_t *labelsptr = 0;
static token_t *tokensptr = 0;

void 
init(program_t *program)
{
    dataptr = 0;
    labelsptr = program->labels;
    tokensptr = program->tokens;
}

void 
lex(char *const src, program_t *program)
{
    labelpass(src, program);
    secondpass(src, program);
}

void 
labelpass(char *const src, program_t *program)
{
    char *line = strtok(src, "\n");
    label_t *label = calloc(1, sizeof(label_t));

    while(line != NULL)
    {
        if(checkfordirective(label, line))
        {
            /* a directive has been found, reserve memory and modify data pointer */
            int step = createdlabel(label, line);

            dataptr += step;
        } else
        {

        }

        line = strtok(NULL, "\n");
    }
}

void 
secondpass(char *const src, program_t *program)
{
    
}







/* STATIC FUNCTION DEFS */
char *getname(int namelen, char *line)
{
    char *buf = calloc(namelen, sizeof(char));
    int i = 0;

    for(; i < namelen; i++)
        buf[i] = line[i];
    buf[namelen] = 0;

    return buf;
}

int 
getnamelength(char *line)
{
    int count = 0;

    while(!(WHITESPACE_CHARACTER_CHECK(*line) || *line == ':'))     /* check for a space,newline,cr,null,colon,tab */
    {
        line++;
        count++;
    }

    line -= count;                                  /* make sure we reset the pointer */

    return count;
}

void 
processline(label_t *label, char *line)
{
    int namelen = getnamelength(line);
    char *name = getname(namelen, line);    /* temporary name buffer */

    /* get the name of the label and store it into the struct */
    label->name = calloc(namelen, sizeof(char));
    strcpy(label->name, name);

    /* get the value of the directive */
    char *directive = strstr(line, directives[label->directive]);
    int index = (directive - line);
    line += index + strlen(directives[label->directive]);
    if(*line == 0)
        errx(-1, "DIRECTIVE DOES NOT HAVE A VALUE!");

    int i = 0;
    for(; i < strlen(line)+1; i++)
    {
        printf("%02x ", line[i]);
    }
    printf("\n");

    free(name); /* no longer need the temporary name buffer */
}

unsigned short 
createdlabel(label_t *label, char *line) /* returns the step for the data ptr */
{
    processline(label, line);

    if (label->name == NULL)
        return 0;

    return 0;
}

unsigned char
checkfordirective(label_t *label, char *line)
{
    int i = 0;
    char *dir = NULL;

    for(; i < NUM_DIRECTIVES; i++)
    {
        dir = strstr(line, directives[i]); /* check if the line contains a valid directive */
        label->directive = i;
        if(dir != NULL)
            return 1;
    }

    return 0;
}