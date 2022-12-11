#include "buffer.h"
#include <linux/slab.h>
#include <linux/string.h>
void swap_struct ( char * a, char * b )
{
    char **tmp;
    tmp = &a;
    memcpy(&a,&b,sizeof(char*));
    memcpy(&b,tmp,sizeof(char*));
    
} /*swaps two values' memory address,   *
   *this is far better...               */

void swap_int(int64_t *a, int64_t *b) {
    int64_t tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
/*But in this case, it's far better to use*
 *usual form of call-by-reference         */



MODULE_LICENSE("GPL");
