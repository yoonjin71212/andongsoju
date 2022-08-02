#include "buffer.h"
#include <linux/string.h>
#include <linux/slab.h>
// add number between two nodes
int8_t between( list * lst , char * item , node * b , node * n ) {
    node * element ;
    if ( ( element = ( node * ) kmalloc ( sizeof ( node ) , GFP_KERNEL ) ) == NULL ) {
        return 1 ;
	}
	if ( ( b != n -> prev ) ) { //you can't push your element when extra nodes are in between of two nodes.
		kfree( element ); //So, I will free allocated node...
		return -1;
	}
    else {
        element -> key = item ; //this is your key.
        b -> next = element ; //node b's next node is your newly added node
        element -> prev = b;  //so new node's previous node is b
        element -> next = n ; // new node's next node is node n;
	n -> prev = element ; // node n's previous node is new node.
    	lst -> size ++ ;      // new_size=old_size+1
    }
    return 0;
}
int8_t enqueue ( list * lst , char * item ) {
	return between ( lst , item , lst -> rear -> prev , lst -> rear ) ;
} // alias for enquque
void enqueue_list ( list * lst , list * lst_target ) {
  list * target = kmalloc ( (size(lst_target)+2)*sizeof (node) * sizeof(ll) , GFP_KERNEL );
	node * push_node;
	node * target_node;
	memcpy ( target , lst_target , (size(lst_target)+2)*sizeof (node) * sizeof(ll) );
	push_node = lst -> rear -> prev;	
	target_node = target -> front -> next;
	push_node -> next = target_node;
	target_node -> prev = push_node;
	target_node -> next = lst -> rear;
	lst -> rear -> prev = target_node;
	lst -> size += target->size ;
	reset_list ( target );
	free_list  ( target );

} // enqueue whole queue
MODULE_LICENSE("GPL");
