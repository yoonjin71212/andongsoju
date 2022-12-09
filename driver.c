#include "buffer.h"
#include <linux/random.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/device/class.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/stat.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/string.h>
#include <asm/uaccess.h>
#define NAME "BUFFER"
int __MAJOR__;
int __MINOR__;
const char * UUID_TEXT="1234567890abcdefghijklmnopqrstuvwxyz";
int8_t err;

DEFINE_MUTEX(mtx);
list * lst;
struct file_operations fops = {
    .read			= device_read,
    .write		=device_write,
    .open		= device_open,
    .release	=device_release,
    .owner		=THIS_MODULE,
    .unlocked_ioctl = io_sort,
};
struct cdev cdev;
struct class *CLASS = NULL;
char * __device_name__;
int cnt=1;
dev_t dev;
char *CLASSNAME;

MODULE_LICENSE("GPL");
void GET_UUID (char * string)
{
    auto int num=0;
    auto int i;
    for(i=0; i<36; i++) {
        if((i==8)|(i==13)|(i==18)|(i==23)) {
            string[i]='-';
        } else {
            get_random_bytes(&num,sizeof(int));
            num%=strlen(UUID_TEXT);
            string[i]=UUID_TEXT[num];
        }
    }
}




int __init init_device (void)
{
    CLASSNAME=kmalloc(sizeof(char)*36,GFP_USER);
    __device_name__=kmalloc(sizeof(char)*36,GFP_USER);
    GET_UUID(CLASSNAME);
    GET_UUID(__device_name__);
    __MAJOR__=MAJOR(dev);
    __MINOR__=MINOR(dev);
    dev=MKDEV(__MAJOR__,__MINOR__);
    err = alloc_chrdev_region(&dev,__MINOR__,cnt,NAME);
    if(err < 0) {
        printk(KERN_ERR "Registering Character Device failed with %d\n", err);
    }
    lst=kmalloc(sizeof(list),GFP_USER);
    init_list(lst);
    cdev_init(&cdev,&fops);
    cdev.owner = THIS_MODULE;
    err = cdev_add(&cdev,dev,cnt);
    if (err<0) {
        printk(KERN_ALERT "cdev_add() failed with error code(%d)", err);
    }

    CLASS=class_create(THIS_MODULE,CLASSNAME);
    if(IS_ERR(CLASS)) {
        printk(KERN_ERR "Creating Character Device Class failed");
    }



    device_create(CLASS,NULL,dev,NULL,__device_name__);
    printk (KERN_INFO "Buffered Device Initialized; Please check /dev/%s\n",__device_name__ );
    return 0;
}
void __exit clean_device(void)
{

    device_destroy(CLASS,dev);
    class_destroy(CLASS);
    cdev_del(&cdev);
    unregister_chrdev_region(dev,1);
    free_list(lst);
    kfree(__device_name__);

}

int device_open (struct inode *inode, struct file *file )
{
    mutex_lock(&mtx);
    return 0;
}
int device_release (struct inode *inode, struct file *file)
{
    mutex_unlock(&mtx);
    return 0;
}

ssize_t device_read (struct file * file,
                     char __user *buf,
                     size_t len,
                     loff_t *offset)
{
    int ret;
    node *nd;
    if ( !lst -> size ) {
        return 0;
    }
    nd = dequeue (lst);
    if(nd==NULL) {
        mutex_unlock(&mtx);
        return 0;
    }
    ret=copy_to_user(buf,nd -> key,nd -> len + 1);
    if((ret<0)) {
        printk( KERN_ERR "Copying data failed with error codes (%d)", ret );
    }
    mutex_unlock(&mtx);
    return (ssize_t)len;
}
ssize_t device_write (struct file * file,
                      const char *buf,
                      size_t len,
                      loff_t *offset)
{
    ssize_t ret = (ssize_t)len;
    int err;
    char * data;
    data=kmalloc(sizeof(char)*BUFFER_MAX,GFP_USER);
    err = copy_from_user(data,buf,len);
    if(err<0) {
        mutex_unlock(&mtx);
        return err;
    }
    if(full(lst)) {
        dequeue(lst);
    }
    enqueue (lst,data,strlen(data));
    mutex_unlock(&mtx);
    return ret;
}

long int __user io_sort(struct file *file, unsigned int cmd, unsigned long arg) {

    switch(cmd) {
        case __CLEAR__:
            empty_list(lst);
            break;  
        case __SORT_ASCENDING__:
            sort_func(lst,1); 
            break;  
        case __SORT_DESCENDING__:
            sort_func(lst,0); 
            break;  
        case __SIZE_CALL__:
            return (long int) size(lst);
        default :
            break;  
    }
    printk(KERN_INFO "IOCTL Called, command number is (%d)", cmd);
    return 0;
}

module_init(init_device);
module_exit(clean_device);

