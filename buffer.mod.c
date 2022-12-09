#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xf01bbbc1, "__class_create" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x2bb7eeeb, "class_destroy" },
	{ 0x37a0cba, "kfree" },
	{ 0x73a0d7e7, "kmem_cache_alloc_trace" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x92997ed8, "_printk" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0x7682ba4e, "__copy_overflow" },
	{ 0xa916b694, "strnlen" },
	{ 0xc5ef1a8b, "cdev_add" },
	{ 0x51a13890, "device_create" },
	{ 0x4dfa8d4b, "mutex_lock" },
	{ 0x449ad0a7, "memcmp" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x3213f038, "mutex_unlock" },
	{ 0x652729fd, "device_destroy" },
	{ 0x41ed3709, "get_random_bytes" },
	{ 0x754d539c, "strlen" },
	{ 0x8501ea51, "cdev_init" },
	{ 0xce06aef3, "kmalloc_caches" },
	{ 0x5b30de00, "cdev_del" },
	{ 0xdf61fd44, "module_layout" },
};

MODULE_INFO(depends, "");

