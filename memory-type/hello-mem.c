#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>    /* kmalloc kfree*/
#include <linux/vmalloc.h> /* vmalloc vfree*/
#include <asm/io.h>        /* ioremap */

MODULE_AUTHOR("voipman");
MODULE_LICENSE("Dual BSD/GPL");

#define ISA_REGION_BEGIN 0xA0000
#define ISA_REGION_END   0x100000

#define MALLOC_SIZE 10
static int kmalloc_kfree(void)
{
	char *buf = (char *)kmalloc(MALLOC_SIZE+1, GFP_KERNEL);
	memset(buf, 'X', MALLOC_SIZE);
	buf[MALLOC_SIZE] = 0x00;
	printk("kmalloc buf ptr:%lu, data:%s\n", (unsigned long)buf, buf);
	kfree(buf);
	return 0;
}

static int vmalloc_vfree(void)
{
	char *buf = (char *)vmalloc(MALLOC_SIZE+1);
	memset(buf, 'X', MALLOC_SIZE);
	buf[MALLOC_SIZE] = 0x00;
	printk("vmalloc buf ptr:%lu, data:%s\n", (unsigned long)buf, buf);
	vfree(buf);
	return 0;
}

static int ioremap_iounmap(void)
{
	char *ptr;
	unsigned int ii;
	char *buf = (char *)ioremap(ISA_REGION_BEGIN, ISA_REGION_END - ISA_REGION_BEGIN);
        buf -= ISA_REGION_BEGIN;
	memset(buf, 'X', MALLOC_SIZE);
	ptr = buf;
	buf[MALLOC_SIZE] = 0x00;
	printk("ioremap buf ptr:%lu, data:%s\n", (unsigned long)buf, buf);
	ptr += MALLOC_SIZE;
	iowrite8((u8)0x31, ptr);
	iowrite16((u16)0x3233, ptr+1);
	iowrite32((u32)0x3435, ptr+3);
	ii = ioread8(ptr);
	printk("ioread8:%x\n", ii);
	ii = ioread16(ptr+1);
	printk("ioread16:%x\n", ii);
	ii = ioread32(ptr+3);
	printk("ioread32:%x\n", ii);
	iounmap(buf);
	return 0;
}

static int get_free_page_demo(void)
{
	unsigned long addr = __get_free_pages(GFP_KERNEL, 0);
	memset((void *)addr, 'X', MALLOC_SIZE);
	*((char *)addr + MALLOC_SIZE) = 0x00;
	printk("get_free_page ptr:%lu, data:%s\n", addr, (char *)addr);
	free_page(addr);
	addr = get_zeroed_page(GFP_KERNEL);
	memset((void *)addr, 'X', MALLOC_SIZE);
	printk("get_zeroed_page ptr:%lu, data:%s\n", addr, (char *)addr);
	free_page(addr);
	return 0;
}


static int hello_init(void)
{
	printk(KERN_ERR"Module, hello memory.\n");
	kmalloc_kfree();
	vmalloc_vfree();
	ioremap_iounmap();
	get_free_page_demo();
	return 0x0;
}

static void hello_exit(void)
{
	printk(KERN_ERR"Module, hello exit.\n");
	return;
}
module_init(hello_init);
module_exit(hello_exit);