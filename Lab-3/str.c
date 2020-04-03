#include "str.h"

#include "gc.h"

#include <string.h>
// void str_cmp(char *a, char *b);
char *str_concat(char *dst, char *src) {
	char *ret = gc_malloc(sizeof(char) * (strlen(src) + strlen(dst) + 1));
	if(dst == 0 && src == 0)
		return 0;
	if(dst == 0)
		return str_duplicate(src);
	if(src == 0)
		return str_duplicate(dst);
	strcpy(ret, dst);
	strcat(ret, src);
	return ret;
}
char *str_duplicate(char *src) {
	if(src == 0)
		return 0;
	char *ret = gc_malloc(sizeof(char) * (strlen(src) + 1));
	strcpy(ret, src);
	return ret;
}