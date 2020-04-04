#include "str.h"

#include "gc.h"

#include <string.h>

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
	if(src == NULL)
		return NULL;
	char *ret = gc_malloc(sizeof(char) * (strlen(src) + 1));
	strcpy(ret, src);
	return ret;
}

char *str_escape(char *src) {
	if(src == 0)
		return 0;
	char *res = str_duplicate(src);
	char *rp = src;
	char *wp = res;
	while(*rp != 0) {
		rp++;
		if(*rp == '\\') {
			rp++;
			switch(*rp) {
				case '"':
				case '\'':
				case '\\':
					*wp = *rp;
					wp++;
					break;
				default:
					*wp = '\\';
					wp++;
					*wp = *rp;
					wp++;
			}
		} else {
			*wp = *rp;
			wp++;
		}
	}
	wp -= 2;
	*wp = 0;
	return res;
}