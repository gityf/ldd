#include <linux/init.h>
#include <linux/module.h>

MODULE_AUTHOR("voipman");
MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void)
{
	printk(KERN_ERR"Module, hello world.\n");
	return 0x0;
}

static void hello_exit(void)
{
	printk(KERN_ERR"Module, hello exit.\n");
	return;
}
module_init(hello_init);
module_exit(hello_exit);
