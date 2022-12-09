#include "buffer.h"
//show list
void show( list *lst, char __user *buf )
{
    node * t;
    for ( t = lst -> front -> next ; t != lst -> rear ; t = t -> next ) { //show all nodes' key
        if(strlen(t->key)<LST_MAX) {
            printk ( "%s\n", (char *)t->key );  //no other data;just the key
        }
    }
    empty_list(lst);
}
MODULE_LICENSE("GPL");
