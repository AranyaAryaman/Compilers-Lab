#ifndef _STR_
#define _STR_

#include "str.h"

typedef struct str {
	char *arr;
	int size;
} str;

char *str_concat(char *dest, char *src);
char *str_duplicate(char *src);
char *str_escape(char *src);

#endif
