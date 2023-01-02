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
#define BUFFER_MAX PREFIX
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
char *NAME;

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
    CLASSNAME=kmalloc(sizeof(char)*36,GFP_KERNEL);
    NAME=kmalloc(sizeof(char)*36,GFP_KERNEL);
    GET_UUID(NAME);   /*Name is by UUID */
    __device_name__=kmalloc(sizeof(char)*36,GFP_KERNEL);
                                 /* * * * * * * * * */
    GET_UUID(CLASSNAME);         /* Class name and  */
    GET_UUID(__device_name__);   /* Device name is  */
    __MAJOR__=MAJOR(dev);        /*   named by      */
    __MINOR__=MINOR(dev);        /*   UUID          */
                                 /* * * * * * * * * */
    dev=MKDEV(__MAJOR__,__MINOR__);
    err = alloc_chrdev_region(&dev,__MINOR__,cnt,NAME);
    if(err < 0) {
        printk(KERN_ERR "Registering Character Device failed with %d\n", err);
    }
    lst=kmalloc(sizeof(list),GFP_KERNEL);    /*List is allocated here*/
    init_list(lst);                          /*Now, this initialized your list.*/
    cdev_init(&cdev,&fops);                  /*Gonna initialize its cdev*/
    cdev.owner = THIS_MODULE;                /*Owner is this module, obviously.*/
    err = cdev_add(&cdev,dev,cnt);           /*Add this into target major/minor number*/
    if (err<0) {
        printk(KERN_ERR "cdev_add() failed with error code(%d)", err);  /* If it fails, it will show this */
    }

    CLASS=class_create(THIS_MODULE,CLASSNAME);  /* Okay, now register its class */
    if(IS_ERR(CLASS)) {
        printk(KERN_ERR "Creating Character Device Class failed");
    }  /* Also, fail check is here */



    device_create(CLASS,NULL,dev,NULL,__device_name__);
    
    printk (KERN_INFO "Buffered Device Initialized; Please check /dev/%s\n",__device_name__ );   /* You can check its location *
                                                                                                  * via dmesg command          */
    return 0;
}
void __exit clean_device(void)
{

    device_destroy(CLASS,dev);   /* destroy its device */
    class_destroy(CLASS);        /* and also its parent*/
    cdev_del(&cdev);             /* delete cdev        */
    unregister_chrdev_region(dev,1);  /* finally, unregister */
    free_list(lst);           /* free that buffer !  */
    kfree(__device_name__);   /* and...free its name */
    kfree(CLASSNAME);

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
    static _Bool readable = 1; /*Read lock*/
    int ret;
    node *nd;
    if(readable==0) {
        readable = 1;
        return (ssize_t)0;
     }
    if ( !lst -> size ) {
        return 0;
    }
    nd = dequeue (lst); /* dequeue its data */
    if(nd==NULL) {
        return 0;
    }
    ret=copy_to_user(buf,nd -> key,nd -> len + 1); /* use its saved length */
    if((ret<0)) {
        printk( KERN_ERR "Copying data failed with error codes (%d)", ret );
    }
    readable = 0;
    return (ssize_t)(nd->len+1);/*use its saved length */
}
ssize_t device_write (struct file * file,
                      const char *buf,
                      size_t len,
                      loff_t *offset)
{
    ssize_t ret = (ssize_t)len;
    int err;
    char * data;
    data=kmalloc(sizeof(char)*BUFFER_MAX,GFP_KERNEL); /*allocates data region */
    err = copy_from_user(data,buf,len);               /*Now, it will copy userdata into kernel area*/
    if(err<0) {
        return err;
    }
    if(full(lst)) {
        dequeue(lst);  /* if it is full, trashes its last data */
    }
    enqueue (lst,data,strlen(data));  /* Enqueue (char *) shaped data */
    return ret;
}

long int __user io_sort(struct file *file, unsigned int cmd, unsigned long arg) {

    /*IOCTL Function calls, by command */
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
    printk(KERN_INFO "IOCTL Called, command number is (%d)", cmd); /*Log for IOCTL */
    return 0;
}

module_init(init_device);
module_exit(clean_device);

