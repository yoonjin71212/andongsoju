#include "buffer.h"
#include <linux/slab.h>
void init_list ( list * lst )   // init list
{
    lst -> front = ( node * ) kmalloc ( sizeof ( node ), GFP_KERNEL ) ;  // front pointer. This is allocated into GFP_KERNEL
    lst -> rear = ( node * ) kmalloc( sizeof ( node ), GFP_KERNEL );  // rear pointer. This is allocated into GFP_KERNEL
    lst -> front -> next = lst -> rear ; //front is directly connected to rear
    lst -> rear -> prev = lst -> front ; //rear is directly connected to front
    lst -> front -> prev = lst -> front -> prev; //close the prev ptr to avoid invalid access
    lst -> rear -> next = lst ->rear ; //close the next ptr to avoid invalid access
    lst -> front -> key = LST_ERR;
    lst -> rear -> key =  LST_ERR;
    lst -> size = 0 ;
}

void reset_list ( list * lst )   // re-init list (reset list)
{
    lst -> front -> next = lst -> rear ;  //front is directly connected to rear; but data is not cleaned ...
    lst -> rear -> prev = lst -> front ;  //rear is directly connected to front...
    lst -> size = 0 ; //size reset;now it's zero again.
}
MODULE_LICENSE("GPL");
