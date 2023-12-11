#include "sabasm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* get the total number of occurences of needle in haystack. */
static int getcharcount(char *haystack, char needle);

static void checknumber(label_t *label, char *directive, char *line);
static void getnumericvalue(char *line, int index, int *value);
static int getchaystackedgecase(char *line, char needle0, char needle1);

static int getnamelength(char *line);
static char *getname(int namelen, char *line);
static void processline(label_t *label, char *line);

static void createdlabel(label_t *label, char *line);

static unsigned char checkfordirective(label_t *label, char *line);
static unsigned char checkforlabel(char *line);

/* define functions, make it easier to define things */
static void definebytesrecursive(label_t *label, char *line, int numBytes, int i);

static unsigned short dataptr = 0;                 /* The current byte in data memory (helps with label declaration) */
static label_t **labelsptr = 0;
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

    while(line != NULL)
    {
        label_t *label = calloc(1, sizeof(label_t));
        
        if(checkfordirective(label, line))
        {
            /* a directive has been found, create it's label signature */
            createdlabel(label, line); /* TODO: What to do about directives not attached to a label? */
            *labelsptr = label;
            labelsptr++;
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
int
getchaystackedgecase(char *line, char needle0, char needle1)
{
    char *comma = strchr(line, needle0);
    if(comma == NULL)
        comma = strchr(line, needle1);
    return (comma - line);
}

void 
getnumericvalue(char *line, int index, int *value)
{
    /* Cannot assume hex, bin, or dec, check for them. */
    if(IS_HEX(line, index))
        *value = strtol(line, NULL, 16);
    else if(IS_BIN(line))
        *value = strtol(line, NULL, 2); /* TODO: prototype binary to decimal conversion */
    else
        *value = strtol(line, NULL, 10);
}

void
definebytesrecursive(label_t *label, char *line, int numBytes, int i)
{
    int numcommas = getcharcount(line, ',');
    label->value = realloc(label->value, numBytes * numcommas);
    int value = 0;
    
    int index = getchaystackedgecase(line, ',', '\0');

    /* temporary buffer for number */
    char temp[index];
    memcpy(temp, line, index);
    temp[index] = 0;

    getnumericvalue(line, index, &value);

    if(numBytes > 1) /* store information about the directive in little endian (specificall for DW/DF) */
    {
        label->value[i] = (value & 0xFF00) >> 8;
        label->value[i + 1] = (value & 0x00FF);
    } else          /* store information as a normal byte */
        label->value[i] = value;

    line += index + 1;
    if(*line == ' ')
        line++;

    numcommas--;
    i += numBytes;

    if(numcommas > 0)
        definebytesrecursive(label, line, numBytes, i);
}

int
getcharcount(char *haystack, char needle)
{
    int i = 0;
    int count = 0;
    for(; i < strlen(haystack) + 1; i++)
    {
        if(haystack[i] == needle)
            count++;
    }

    return count + 1;
}

void 
checknumber(label_t *label, char *directive, char *line)
{
    if(IS_NUMBER(*line)) /* check if the first character in the line is a number character */
    {
        if(strncmp(directive, "DB", 2) == 0)
        {
            label->value = calloc(1, sizeof(char));
            definebytesrecursive(label, line, 1, 0);
            /* definebytes(label, line, 1); */
        } else if(strncmp(directive, "DW", 2) == 0)
        {
            label->value = calloc(2, sizeof(char));
            definebytesrecursive(label, line, 2, 0);
            /* definebytes(label, line, 2); */
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

    label->name = calloc(namelen, sizeof(char));
    strcpy(label->name, name);

    /* get the value of the directive */
    char *directive = strstr(line, directives[label->directive]);
    int index = (directive - line);
    /* 
        modify the line pointer to make it easier to process the arguments of the directive. 
        add 1 to avoid spacing issue
    */
    line += index + strlen(directives[label->directive]) + 1; 
    if(*line == 0)
        errx(-1, "DIRECTIVE DOES NOT HAVE A VALUE!");

    checknumber(label, directive, line);

    free(name); /* no longer need the temporary name buffer */
}

void 
createdlabel(label_t *label, char *line)
{
    processline(label, line);

    if (label->name == NULL || label->value == NULL)
        return;
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