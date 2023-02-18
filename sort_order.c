#include "buffer.h"
#include <linux/string.h>
#include <linux/slab.h>

_Bool __order_regen_sorted__ ( list * lst, _Bool is_ascending)
{
    node * nd;
    _Bool ret = 0;
    for (nd = lst -> front -> next; nd!=lst->rear->prev; nd=nd->next) {
        ret=(!comp(nd->__len_key__,nd->next->__len_key__,is_ascending));
        if (ret) {
            break;
        }
    }
    return !ret;
    /*regeneration of its state, for accurate status update*/
}

void __order_sortthree__ ( list * lst, _Bool is_ascending)
{
    node * mid;
    node * front = lst -> front -> next ;
    node * rear = lst -> rear -> prev ;
    mid = index_node ( lst, ( ll )( lst -> size / 2) ) ;
    if(lst->is_sorted) {
        return ;
    }
    if (comp(front->__len_key__, mid->__len_key__,is_ascending) ) {
        swap_int (&front->__len_key__,&mid->__len_key__);
        swap_struct ( front->key,mid->key );
    }
    if (comp(front->__len_key__, rear->__len_key__,is_ascending) ) {
        swap_int ( &front->__len_key__,&rear->__len_key__);
        swap_struct ( front->key,rear->key );
    }
    if ( comp(mid->__len_key__, rear->__len_key__,is_ascending) ) {
        swap_int ( &mid->__len_key__,&rear->__len_key__);
        swap_struct ( mid->key, rear->key );
    }
    /* Sort picked three nodes, by its length */

}
void __order_sort_func__ ( list * lst, _Bool is_ascending )
{
    int sz = lst -> size ;
    char *key;
    node *piv,*track;
    uint64_t len;
    list llst, rlst ;
    if ( lst -> size < 2 ) {
        return;
    }
    init_list (&llst);
    init_list (&rlst);
    __order_sortthree__( lst, is_ascending );
    piv = index_node ( lst, lst->size/2 ) ;
    track = lst -> front -> next;
    for ( ; track != lst -> rear ; track = track -> next ) {
        key = piv -> key;
        len = piv -> len;
        if ( piv  == track ) {
            continue;
        }
        if ( comp(track -> len, piv -> len, is_ascending) ) {
            enqueue ( &llst, track -> key, track -> len );
        } else {
            enqueue ( &rlst, track -> key, track -> len );
        }
        /* Split its keys by length */
    }
    empty_list ( lst ); /*Preparing to sort...*/
    if ( llst.size > 1 ) {
        __order_sort_func__ ( &llst, is_ascending ) ;  /* recursive function calls*/
    }
    if ( rlst.size > 1 ) {
        __order_sort_func__ ( &rlst, is_ascending ) ; /*  recursive function calls*/
    }
    /* Concatenates its left-ordered list */
    if ( llst.size > 0 ) {
        concat_list(lst,&llst);
    }
    /* Concatenates its right-ordered list */
    enqueue( lst, key, len );
    if ( rlst.size > 0 ) {
        concat_list(lst,&rlst);
    }
    lst -> size = sz ;
    lst -> is_sorted = __order_regen_sorted__(lst,is_ascending);
    /* Regenerate its flag*/
}
