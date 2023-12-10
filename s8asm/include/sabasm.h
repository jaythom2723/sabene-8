#ifndef SAB_ASM_H
#define SAB_ASM_H

#include "asmdefs.h"

void lex(program_t *program);         /* Calls labelpass, secondpass internally */

void labelpass();                     /* Check for labels/variables/constants */
void secondpass();                    /* Lexalize rest of lines */

#endif /* SAB_ASM_H */