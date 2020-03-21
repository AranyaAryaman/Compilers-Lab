#ifndef _GC_
#define _GC_

#include <stdio.h>

typedef struct gc_ptr {
	void *ptr;
} gc_ptr;

void gc_init();
void *gc_malloc(size_t s);
void gc_destroy();
void gc_collect();

extern gc_ptr *ptr_arr;
extern int size;
extern int c;
extern int init_done;

#endif