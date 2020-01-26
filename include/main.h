#ifndef _MAIN_
#define _MAIN_

#include <stdio.h>

#define _DEBUG_ 0
extern FILE *input_file;
extern FILE *output_file;
extern FILE *lex_file;
extern char *input_filename;

void err(char *str, ...);

#endif
