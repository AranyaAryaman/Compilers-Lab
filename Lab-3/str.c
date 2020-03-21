#include "str.h"

#include "gc.h"

#include <string.h>
// void str_cmp(char *a, char *b);
char *str_concat(char *dst, char *src) {
	char *ret = gc_malloc(sizeof(char) * (strlen(src) + strlen(dst) + 1));
	strcpy(ret, dst);
	strcat(ret, src);
	return ret;
}
char *str_duplicate(char *src) {
	char *ret = gc_malloc(sizeof(char) * (strlen(src) + 1));
	strcpy(ret, src);
	return ret;
}