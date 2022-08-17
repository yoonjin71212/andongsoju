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
#include <linux/ktime.h>
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
extern int8_t enqueue(list * lst , char * item);
extern char * dequeue(list * lst);

list * lst;
struct file_operations fops = {
	.read			= device_read,
	.write		=device_write,
	.open		= device_open,
	.release	=device_release,
	.owner		=THIS_MODULE
};
struct cdev cdev;
struct class *CLASS = NULL;
char * __device_name__;
int cnt=1;
dev_t dev;
char *CLASSNAME;

MODULE_LICENSE("GPL");
void GET_UUID (char * string) {
	auto int num=0;
	auto int i;
	for(i=0;i<36;i++) {
		if((i==8)|(i==13)|(i==18)|(i==23)) {
			string[i]='-';
		} else {
			get_random_bytes(&num,sizeof(int));
			num%=strlen(UUID_TEXT);
			string[i]=UUID_TEXT[num];
		}
	}
	
}




int __init init_device (void) {
	CLASSNAME=kmalloc(sizeof(char)*36,GFP_KERNEL);
	__device_name__=kmalloc(sizeof(char)*36,GFP_KERNEL);
	GET_UUID(CLASSNAME);
	GET_UUID(__device_name__);
	__MAJOR__=MAJOR(dev);
	__MINOR__=MINOR(dev);
	dev=MKDEV(__MAJOR__,__MINOR__);
	err = alloc_chrdev_region(&dev,__MINOR__,cnt,NAME);
	if(err < 0) {
		printk(KERN_ERR "Registering Character Device failed with %d\n", err);
	}
	lst=kmalloc(sizeof(list),GFP_KERNEL);
	init_list(lst);
	cdev_init(&cdev,&fops);
	cdev.owner = THIS_MODULE;
	err = cdev_add(&cdev,dev,cnt);
	if (err<0) {
		printk(KERN_ALERT "cdev_add() failed with error code(%d)" , err);
	}
	
	CLASS=class_create(THIS_MODULE,CLASSNAME);
	if(IS_ERR(CLASS)) {
		printk(KERN_ERR "Creating Character Device Class failed");
	}


		
	device_create(CLASS,NULL,dev,NULL,__device_name__);
	printk (KERN_INFO "Buffered Device Initialized; Please check /dev/%s\n",__device_name__ );
	return 0;
}
void __exit clean_device(void) {

	
	device_destroy(CLASS,dev);	
	class_destroy(CLASS);
	cdev_del(&cdev);
	unregister_chrdev_region(dev,1);
	free_list(lst);
	kfree(__device_name__);
}

int device_open (struct inode *inode , struct file *file ) {
	try_module_get(THIS_MODULE);	
	return 0;
}
int device_release (struct inode *inode , struct file *file) {
	return 0;
}

ssize_t device_read (struct file * file,
				char __user *buf,
				size_t len,
				loff_t *offset) {
	int ret;
	char * data = dequeue (lst);
	if ( lst -> size == 0 ) 
		return 0;
		
	ret=copy_to_user(buf,data,sizeof(char *));
	if((ret<0)) {
		printk( KERN_ERR "Copying data failed with error codes (%d)", ret);
	}
	lst->size--;
	return (ssize_t)len;
}
ssize_t device_write (struct file * file,
														const char *buf,
														size_t len,
														loff_t *offset) {
	char * data;
	ktime_t tmp;
	ssize_t ret = (ssize_t)len;
	tmp=ktime_get_real();
	data=kmalloc(sizeof(char)*(len),GFP_KERNEL);
	err = copy_from_user(data,buf,len);
			
	if(full(lst)) {
		dequeue(lst);
	}

	enqueue ( lst , data);
	lst->size++;
	return ret;
}
module_init(init_device);
module_exit(clean_device);

