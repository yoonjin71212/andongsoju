#include "buffer.h"
#include <linux/string.h>
#include <linux/slab.h>
// add number between two nodes
int8_t between( list * lst, char * item, node * b, node * n , uint64_t len )
{
    node * element ;
    if ( ( element = ( node * ) kmalloc ( sizeof ( node ), GFP_KERNEL ) ) == NULL ) {
        return 1 ;
    }
    element->key = LST_ERR;
    if ( ( b != n -> prev ) ) { //you can't push your element when extra nodes are in between of two nodes.
        kfree( element ); //So, I will free allocated node...
        return -1;
    } else {
        element -> key = item ; //this is your key.
        element -> len  = len;
        b -> next = element ; //node b's next node is your newly added node
        element -> prev = b;  //so new node's previous node is b
        element -> next = n ; // new node's next node is node n;
        n -> prev = element ; // node n's previous node is new node.
        lst -> size ++ ;      // new_size=old_size+1
    }
    return 0;
}
int8_t enqueue ( list * lst, const char * item , uint64_t len)
{
    return between ( lst, (char *)item, lst-> rear -> prev ,  lst -> rear , len);
} // alias for enquque
void concat_list ( list * lst, list * lst_target )
{
    node * push_node;
    node * target_node;
    node * target_end;
    push_node = lst -> rear -> prev;
    target_node = lst_target -> front -> next;
    target_end  = lst_target -> rear -> prev;
    push_node -> next = target_node;
    target_node -> prev = push_node;
    target_end -> next = lst -> rear;
    lst -> rear -> prev = target_end;
    lst -> size += lst_target->size ;
    kfree (lst_target->front);
    kfree (lst_target->rear);

} // enqueue whole queue
MODULE_LICENSE("GPL");
