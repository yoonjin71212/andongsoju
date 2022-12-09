#include "buffer.h"

// return size of list
ll size ( list * lst )
{
    return lst -> size ;
}
void repair_size ( list * lst )   //you can use it when size could be corrupted by some reasons
{
    node *nd ;
    ll sz = 0;
    for ( nd = lst -> front -> next ; nd != lst -> rear ; nd = nd -> next ) {
        sz ++; //count all nodes while it meets its rear
    }
    lst -> size = sz; //now, size is corrected. Applying new size to corrupted data...

}
// check if list is full
int8_t full ( list * lst )
{
    if ( lst -> size == LST_MAX ) { // if list size is at its end
        return 1 ;  //Returns 1
    }

    else {
        return 0 ; //if it is okay, Returns 0
    }
}
MODULE_LICENSE("GPL"); /*You need to use GPL-compatible license to use this in your kernel.
			If you modified your kernel source-code to avoid GPL Check, you can comment this line..*/
