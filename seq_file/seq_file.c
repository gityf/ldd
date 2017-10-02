#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/random.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/list.h>

#define RANDOM_INFO_SIZE 50
#define SEQ_FILE_NAME "seq_file_hello"

typedef struct hello_random_s {
    struct list_head list;
    char info[RANDOM_INFO_SIZE];
} hello_random_t;

static LIST_HEAD(hello_list);

static void *seq_start(struct seq_file *m, loff_t *pos)
{
    printk("seq_start pos:%d, buf:%s\n", *pos, m->buf);
    return seq_list_start(&hello_list, *pos);;	
}

static void seq_stop(struct seq_file *m, void *v)
{
    printk("seq_stop buf:%s\n", m->buf);
    /* No cleanup needed in this example */
}

static void *seq_next(struct seq_file *m, void *v, loff_t *pos)
{
    printk("seq_next pos:%d, buf:%s\n", *pos, m->buf);
    return seq_list_next(v, &hello_list, pos);
}

static int seq_show(struct seq_file *m, void *v)
{
    const struct hello_random_s *p = list_entry(v, struct hello_random_s, list);
    
    
    printk("seq_show buf:%s\n", m->buf);
    seq_printf(m, "%s", p->info);
		
    return 0;
}

static const struct seq_operations seq_hello_ops = {
	.start  = seq_start,
	.next   = seq_next,
	.stop   = seq_stop,
	.show   = seq_show,
};

static int seq_hello_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &seq_hello_ops);
}

static const struct file_operations seq_hello_fops = {
	.owner		= THIS_MODULE,
	.open		= seq_hello_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= seq_release,
};

static int __init seq_hello_init(void)
{
    int i, count;
    struct hello_random_s *mylist_node;
    struct proc_dir_entry *p;

    p = proc_create(SEQ_FILE_NAME, S_IRUGO, NULL, &seq_hello_fops);
    if (!p)
	goto out;

    for(i = 0; i < 10; i++) {
	mylist_node = kmalloc(sizeof(struct hello_random_s), GFP_ATOMIC);
	if (!mylist_node)
	    return -ENOMEM;
	memset(mylist_node, 0, sizeof(struct hello_random_s));
	get_random_bytes(&count, sizeof(int));
	sprintf(mylist_node->info, "random number %d: %d\n", i, count);
	printk("%s", mylist_node->info);
	list_add_tail(&mylist_node->list, &hello_list);
    }
    
    return 0;
out:
    remove_proc_entry(SEQ_FILE_NAME, NULL);
    return -EFAULT;
}

static void __exit seq_hello_exit(void)
{
    struct list_head *p, *q;
    struct hello_random_s *mylist_node;

    list_for_each_safe(p, q, &hello_list) {
	mylist_node = list_entry(p, struct hello_random_s, list);
	list_del(p);
	kfree(mylist_node);
    }

    remove_proc_entry(SEQ_FILE_NAME, NULL);
}

module_init(seq_hello_init);
module_exit(seq_hello_exit);

MODULE_AUTHOR("voipman");
MODULE_LICENSE("Dual BSD/GPL");

