#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/delay.h>

MODULE_AUTHOR("voipman");
MODULE_LICENSE("Dual BSD/GPL");

struct timer_list timer1;
struct timer_list timer2;
struct timer_list timer3;
struct timer_list timer4;

void timer_func(unsigned long data) {
	struct timer_list *data_ptr = (struct timer_list *) data;
	printk("timer_func data:%lu, expires:%lu\n", data, data_ptr->expires);
}

static void add_timer_func(struct timer_list *timer) {
	init_timer(timer);
	timer->data = (unsigned long)timer;
	timer->function = timer_func;
	timer->expires = jiffies + 10;
	add_timer(timer);
}

static void timer_demo()
{
	printk("timer_demo init_timer\n");
	
	add_timer_func(&timer1);
	mdelay(100);
	add_timer_func(&timer2);
	mdelay(100);
	add_timer_func(&timer3);
	add_timer_func(&timer4);
	printk("after add_timer\n");

	del_timer(&timer3);
	printk("after del_timer\n");
}

static int hello_init(void)
{
	printk(KERN_ERR"Module, hello timer.\n");
        timer_demo();
	return 0x0;
}

static void hello_exit(void)
{
	printk(KERN_ERR"Module, hello timer exit.\n");
	return;
}
module_init(hello_init);
module_exit(hello_exit);
