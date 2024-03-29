#include "stdtype.h"


#ifndef ATAG_H
#define ATAG_H




enum atag_tag_t {
	NONE		= 0x00000000,
	CORE		= 0x54410001,
	MEM			= 0x54410002,
	VIDEOTEXT	= 0x54410003,
	RAMDISK		= 0x54410004,
	INITRD2		= 0x54420005,
	SERIAL		= 0x54420006,
	REVISION	= 0x54420007,
	VIDEOLFB	= 0x54420008,
	CMDLINE 	= 0x54410009,
};

struct mem_t {
	u32 start;
	u32 size;
};

struct initrd2_t {
	u32 start;
	u32 size;
};

struct cmdline_t {
	char line[1];
};

typedef struct atag{
	u32 tag_size;
	enum atag_tag_t tag;
	union {
		struct mem_t mem;
		struct initrd2_t initrd2;
		struct cmdline_t cmdline;
	};
}atag_t;

#endif