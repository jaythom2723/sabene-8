#include "sabasm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void checknumber(label_t *label, char *directive, char *line);

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
void 
checknumber(label_t *label, char *directive, char *line)
{
    if(IS_NUMBER(*line)) /* check if the first character in the line is a number character */
    {
        /* create a buffer that contains the whole number */
        char *nt = strchr(line, '\0');
        int index = (nt - line);
        char temp[index];
        memcpy(temp, line, index);
        temp[index] = 0;

        if(strncmp(directive, "DB", 2) == 0)
        {

        } else if(strncmp(directive, "DW", 2) == 0)
        {
            /* Check for comma separated defintions (WIP) */
            char *comma = strtok(line, ",");
            int count = 0;
            while(comma != NULL)
            {
                count++;
                comma = strtok(NULL, ",");
            }

            label->value = calloc(2 * count, sizeof(char)); /* TODO: prototype comma-separated word definition */
            int value = 0;

            /* We cannot assume that the number has the hexadecimal denotifier(s), we must check for them */
            if(IS_HEX(line, index))
                value = strtol(line, NULL, 16);
            else
                value = strtol(line, NULL, 10);

            /* Storing the data into the label's value array in little endian format */
            label->value[0] = (value & 0x00FF);
            label->value[1] = (value & 0xFF00) >> 8;
        } else if(strncmp(directive, "DF", 2) == 0) 
        {
            /* TODO: IEEE 754 standard algorithm */

            /* NOTE: Remember to store data into the label's value little endian style! */

            /* Floating point values are all 16-bits (The ALU can support floating point number arithmetic) */
            /* IEEE 754 describes 1-bit for signage, 5-bit exponent value, and 10-bit fraction value */
        
        
            /* We can assume that the number has a '.' in the line, since we're using the DF directive */
            
        }
    }
}

char *
getname(int namelen, char *line)
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

    while(!(WHITESPACE_CHARACTER_CHECK(*line) || *line == ':')) /* check for a space,newline,cr,null,colon,tab */
    {
        line++;
        count++;
    }

    line -= count; /* make sure we reset the pointer */

    return count;
}

void 
processline(label_t *label, char *line)
{
    int namelen = getnamelength(line);
    char *name = getname(namelen, line); /* temporary name buffer */

    /* get the name of the label and store it into the struct */
    label->name = calloc(namelen, sizeof(char));
    strcpy(label->name, name);

    /* get the value of the directive */
    char *directive = strstr(line, directives[label->directive]);
    int index = (directive - line);
    line += index + strlen(directives[label->directive]) + 1; /* modify the line pointer to make it easier to process the arguments of the directive. */
    if(*line == 0)
        errx(-1, "DIRECTIVE DOES NOT HAVE A VALUE!");

    checknumber(label, directive, line);

    free(name); /* no longer need the temporary name buffer */
}

unsigned short 
createdlabel(label_t *label, char *line) /* returns the step for the data ptr */
{
    processline(label, line);

    if (label->name == NULL)
        return 0;

    return 1;
}

unsigned char
checkfordirective(label_t *label, char *line)
{
    int i = 0;
    char *dir = NULL;

    for(; i < NUM_DIRECTIVES; i++)
    {
        dir = strstr(line, directives[i]); /* check if the line contains a valid directive */
        label->directive = i;              /* give a hint to the lexer about what the directive is for the given label */
        if(dir != NULL)
            return 1;
    }

    return 0;
}