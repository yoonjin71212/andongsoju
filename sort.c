#include "buffer.h"
#include <linux/string.h>
#include <linux/slab.h>
_Bool comp( ll len_l, ll len_r, _Bool is_ascending ) {
    if (is_ascending) {
        return (_Bool)(len_r-len_l>=0);
    } else {
        return (_Bool)(len_l-len_r>=0);
    }
}
_Bool regen_sorted( list * lst , _Bool is_ascending) {
    node * nd;
    _Bool ret = 0;
    for (nd = lst -> front -> next;nd!=lst->rear->prev;nd=nd->next) {
        ret=(!comp(nd->len,nd->next->len,is_ascending));
        if (ret) {
            break;
        }
    }
    return !ret;
}

void sortthree ( list * lst , _Bool is_ascending)
{
    node * mid; 
    node * front = lst -> front -> next ;
    node * rear = lst -> rear -> prev ;
    mid = index_node ( lst, ( ll )( lst -> size / 2) ) ;
    if(lst->is_sorted) {
        return ;
    }
    if (comp(front->len , mid->len,is_ascending) ) {
        swap_int (&front->len,&mid->len);
        swap_struct ( front->key,mid->key );
    }
    if (comp(front->len , rear->len,is_ascending) ) {
        swap_int ( &front->len,&rear->len);
        swap_struct ( front->key,rear->key );
    }
    if ( comp(mid->len , rear->len,is_ascending) ) {
        swap_int ( &mid->len,&rear->len);
        swap_struct ( mid->key, rear->key );
    }
	
}
void sort_func ( list * lst , _Bool is_ascending )
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
    sortthree( lst , is_ascending );
    piv = index_node ( lst, lst->size/2 ) /*lst -> front -> next*/;
                track = lst -> front -> next;
    for ( ; track != lst -> rear ; track = track -> next ) {
        key = piv -> key;
        len = piv -> len;
        if ( piv  == track ) {
            track = track -> next ;
            continue;
        }
        if ( comp(track -> len , piv -> len, is_ascending) ) {
            enqueue ( &llst, track -> key , track -> len );
        } else {
            enqueue ( &rlst, track -> key , track -> len );
        }
    }
    empty_list ( lst );
    if ( llst.size > 1 ) {
        sort_func ( &llst , is_ascending ) ;
    }
    if ( rlst.size > 1 ) {
        sort_func ( &rlst, is_ascending ) ;
    }
    if ( llst.size > 0 ) {
        concat_list(lst,&llst);
    }
    enqueue( lst, key , len );
    if ( rlst.size > 0 ) {
        concat_list(lst,&rlst);
    }
    lst -> size = sz ;
    lst -> is_sorted = regen_sorted(lst,is_ascending);
}
