#ifndef SAB_ASM_H
#define SAB_ASM_H

#include "asmdefs.h"

void init(program_t *program);

void lex(char *const src, program_t *program);         /* Calls labelpass, secondpass internally */

void labelpass(char *const src, program_t *program);                     /* Check for labels/variables/constants */
void secondpass(char *const src, program_t *program);                    /* Lexalize rest of lines */

#endif /* SAB_ASM_H */