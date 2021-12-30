#include "stdtype.h"
#include "atag.h"
#include "mem.h"

static u32 num_pages;

/* Gets the total memory size from the atags. */
u32 get_mem_size (struct atag_t *tag)
{
	while (tag->tag != NONE) {
		if (tag->tag == MEM)
			return tag->mem.size;
		tag = (struct atag_t *)(((u32 *)tag) + tag->tag_size);
	}
	return 0;
}

u32 memory_init(struct atag_t *atags){
    u32 mem_size;

    mem_size = get_mem_size(atags);
    num_pages = mem_size / PAGE_SIZE;

	return 1;
}