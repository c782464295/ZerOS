#include "stdtype.h"
#include "atag.h"

#ifndef MEM_H
#define MEM_H



/* Base memory structure:
 * 4KB Page
 * 4KB Kernel Stack
 * 1MB Kernel Heap
 */
enum {
	PAGE_SIZE		    = 4096,
	KERNEL_STACK_SIZE	= PAGE_SIZE,
	KERNEL_HEAP_SIZE	= (1024*1024),
};


/* Flag struct for each memory page. */
struct page_flags_t {
	u8 allocated: 1;		/* currently allocated? */
	u8 kernel_page: 1;		/* part of the kernel? */
	u8 kernel_heap_page: 1;	/* part of the kernel heap? */
	u32 reserved: 29;
};

 /* Struct for each heap segment. */
typedef struct heap_segment {
	struct heap_segment * next;
	struct heap_segment * prev;
	u32 is_allocated;		/* This segment is allocated. */
	u32 segment_size;		/* Size of this segment,
					 *  including this header. */
} heap_segment_t;


/**
 * Heap Stuff
 */
static void heap_init(u32 heap_start);

void mem_init(atag_t* atags);


void* kmalloc(u32 bytes);

void kfree(void *ptr);

#endif