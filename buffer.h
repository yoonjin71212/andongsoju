#include <linux/init.h>
#include <linux/ktime.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <asm/uaccess.h>
#include "buffer_io.h"
#define TEMP_SIZE 128
typedef long long ll;

typedef struct node {
    char * key;
    uint64_t len;
    struct node * prev;
    struct node * next;
} node;

typedef struct list {
    _Bool is_sorted;
    node *front;
    node *rear;
    ll size;
} list;

void init_list ( list * lst );
void reset_list ( list * lst );
int8_t between  ( list * lst, char * item, node * r, node * element , uint64_t len) ;
int8_t enqueue ( list * lst, const char * item , uint64_t len) ;
void concat_list ( list * lst, list * lst_target ) ;

node * remove_item ( list * lst, node * element ) ;
node * dequeue ( list * lst ) ;
ll size ( list *lst ) ;
int str_size(char *str, int prefix);

void repair_size ( list *lst ) ;
int8_t full ( list * lst ) ;
void show ( list * lst, char __user *buf ) ;
void free_list ( list * lst ) ;
void empty_list ( list * lst ) ;
node * find ( list * lst, unsigned char * key ) ;
node * index_node ( list * lst, ll i ) ;

void swap_struct ( char * a, char * b );
void swap_int( int64_t * a, int64_t * b );

int __init init_device (void);
void __exit clean_device(void);
int device_open (struct inode *, struct file *);
int device_release (struct inode *, struct file * );
ssize_t device_read (struct file *, char *, size_t, loff_t *);
char * find_uuid(char * buf) ;
void set_dir (char * folder);
ssize_t device_write (struct file *, const char *, size_t, loff_t *);
void GET_UUID (char * string) ;
void sort_func ( list * lst , _Bool is_ascending );
void sortthree ( list * lst , _Bool is_ascending );
ll index_of(list *lst , node *nd);
long int __user io_sort(struct file *file, unsigned int cmd, unsigned long arg);
_Bool comp(ll len_l, ll len_r, _Bool is_ascending);
#define PREFIX 4096
#define BUFFER_MAX PREFIX
#define LST_MAX 10000
#define UUID_LEN 36
 
