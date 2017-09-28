#include <linux/list.h> 
#include <linux/init.h>
#include <linux/module.h>

MODULE_AUTHOR("voipman");
MODULE_LICENSE("Dual BSD/GPL");

#define MAX_NAME_LEN 32

typedef struct node_s
{
    struct list_head list;
    char name[MAX_NAME_LEN];
    int id;
} node_t;

static void node_print(struct list_head *head) {
    node_t *entry;
    struct list_head *p;
    
    list_for_each(p, head)
    {
        entry=list_entry(p,struct node_s,list);
        printk("name: %s\n",entry->name);
        printk("id: %d\n",entry->id);
    }
}

static int list_demo() {
    struct list_head head;
    struct list_head head2;
    node_t node_1;
    node_t node_2;
    node_t node_3;
    node_t node_4;

    INIT_LIST_HEAD(&head);
    INIT_LIST_HEAD(&head2);

    strcpy(node_1.name, "node1");
    node_1.id = 1;

    strcpy(node_2.name, "node2");
    node_2.id = 2;

    strcpy(node_3.name, "node3");
    node_3.id = 3;

    strcpy(node_4.name, "node4");
    node_4.id = 4;

    list_add(&node_1.list, &head);
    list_add(&node_2.list, &head);
    list_add(&node_3.list, &head);
    list_add_tail(&node_4.list, &head);
    printk("list_add node_1,2,3,4\n");
    node_print(&head);

    list_move(&node_3.list, &head2);
    printk("after list_move node_3\n");
    node_print(&head);
    printk("head2 list node\n");
    node_print(&head2);

    list_move_tail(&node_4.list, &head2);
    printk("after list_movei_tail node_4\n");
    node_print(&head);
    printk("head2 list node\n");
    node_print(&head2);

    list_del(&node_1.list);
    printk("after list_del node_1\n");
    node_print(&head);
    
    list_del(&node_2.list);
    printk("after list_del node_2\n");
    node_print(&head);
    
    list_del(&node_4.list);
    printk("head2  after list_del node_4\n");
    node_print(&head2);
    
    list_del(&node_3.list);
    printk("after list_del node_3\n");
    node_print(&head2);
    
    return 0;
}

static int hello_init(void)
{
    printk(KERN_ERR"Module, hello list init.\n");
    list_demo();
    return 0;
}

static void hello_exit(void)
{
	printk(KERN_ERR"Module, hello list exit.\n");
	return;
}
module_init(hello_init);
module_exit(hello_exit);
