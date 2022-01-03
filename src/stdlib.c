#include "stdtype.h"
/* Public domain.  */
void *memset(void *dest, u32 val, size_t len){
    u8 *ptr = dest;
    while (len-- > 0)
        *ptr++ = val;
    return dest;
}

void bzero(void *to, size_t count){
    memset (to, 0, count);
}

void *memcpy(void *dest, const void *src, size_t len){
    char *d = dest;
    const char *s = src;
    while (len--)
        *d++ = *s++;
    return dest;
}
