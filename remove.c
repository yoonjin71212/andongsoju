#include "buffer.h"
#include <linux/ktime.h>
#include <linux/slab.h>
const ktime_t TS_ZERO = {0};
// function that removes the item
char * remove_item ( list * lst, node * element )
{
    char * val;
    if ( element == lst->front ) { //you cannot remove the front
        return val;

    }	else if ( element == lst->rear ) { //you cannot remove the rear, too
        return val;
    } else if ( lst -> size == 0 ) { //nothing is here. nothing.
        return val;
    } else {
        node * n = element -> next; //element's next node is n.
        node * p = element -> prev; //element's previous node is p.
        n -> prev = p; //skip the element, re-connect previous node as p
        p -> next = n; //skip the element, re-connect next node as n;
        val = element -> key ; //element->key will be the return value.
        kfree ( element ) ;  //successfully deleted
        lst -> size -- ;     //new_size=old_size-1
    }
    return val ; //return the value.
}
char * dequeue ( list * lst )
{
    char * i = remove_item ( lst, lst -> rear -> prev ) ;
    return i;
} //alias to dequeue action
MODULE_LICENSE("GPL");
