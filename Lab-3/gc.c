
#include "gc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int size = 100;
gc_ptr *ptr_arr = NULL;
int c = 0;
int init_done = 0;

void gc_init() {
	if(init_done)
		return;
	c = 0;
	size = 100;
	ptr_arr = 0;
	ptr_arr = malloc(sizeof(gc_ptr) * size);
	if(ptr_arr == NULL) {
		perror("Malloc error");
		exit(0);
	}
	memset(ptr_arr, 0, sizeof(gc_ptr) * size);
	init_done = 1;
}

void *gc_malloc(size_t s) {
	void *ret = malloc(s);
	if(ret == NULL) {
		perror("Malloc error");
		exit(0);
	}
	if(c == size) {
		size *= 2;
		ptr_arr = realloc(ptr_arr, sizeof(gc_ptr) * size);
	}
	ptr_arr[c].ptr = ret;
	c++;
	return ret;
}

void gc_destroy() {
	if(!init_done)
		return;
	for(int i = 0; i < c; i++)
		if(ptr_arr[i].ptr != NULL) {
			free(ptr_arr[i].ptr);
			ptr_arr[i].ptr = NULL;
		}
	free(ptr_arr);
	ptr_arr = NULL;
	c = 0;
	init_done = 0;
}

void gc_collect() {
	gc_destroy();
	gc_init();
}