#include "stdtype.h"
#include "atag.h"
#include "list.h"
#include "mem.h"


static u32 num_pages;

/* Gets the total memory size from the atags. */
u32 get_mem_size (atag_t *atag)
{
	while (atag->tag != NONE) {
		if (atag->tag == MEM)
			return atag->mem.size;
		atag = (atag_t*)(((u32 *)atag) + atag->tag_size);
	}
	return 0;
}

u32 memory_init(atag_t *atags){
    u32 mem_size;

    mem_size = get_mem_size(atags);
    num_pages = mem_size / PAGE_SIZE;

	return 1;
}
static heap_segment_t * heap_segment_list_head;

static void heap_init(u32 heap_start){
	heap_segment_list_head = (heap_segment_t *) heap_start;
	heap_segment_list_head->segment_size = KERNEL_HEAP_SIZE;
}





void test(void){


	DEFINE_LIST(page);
	
	typedef struct page{
		u32 vaddr_mapped;	// The virtual address that maps to this page	
		u32 flags;
		DEFINE_LINK(page);
	}page_t;

	page_list_t free_pages;

	INITIALIZE_LIST(free_pages);

	IMPLEMENT_LIST(page);
}