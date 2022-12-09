#include "buffer.h"
#include <linux/slab.h>
#include <linux/string.h>
void swap_struct ( char * a, char * b )
{
    char **tmp;
    tmp = &a;
    memcpy(&a,&b,sizeof(char*));
    memcpy(&b,tmp,sizeof(char*));
    
} //swaps two values.

void swap_int(int64_t *a, int64_t *b) {
    int64_t tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}



MODULE_LICENSE("GPL");
