#include <linux/init.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/seqlock.h>
#include <linux/mutex.h>
#include <linux/rcupdate.h>
#include <linux/semaphore.h>
#include <linux/rwsem.h>
#include <linux/timer.h>
#include <linux/completion.h>
#include <linux/sched.h>

MODULE_AUTHOR("voipman");
MODULE_LICENSE("Dual BSD/GPL");

spinlock_t my_spin_lock;

static void spin_lock_func(void) {
	spin_lock_init(&my_spin_lock);
	spin_lock(&my_spin_lock);
	printk("spin_lock_func-spin_lock init lock unlock\n");
	spin_unlock(&my_spin_lock);
}

seqlock_t my_seq_lock;

static void seq_lock_func(void) {
	unsigned int seq;
	
	seqlock_init(&my_seq_lock);
	write_seqlock(&my_seq_lock);
	printk("seq_lock_func- wirte_seq_lock/unlock \n");
	write_sequnlock(&my_seq_lock);
	do {
		seq = read_seqbegin(&my_seq_lock);
	} while(read_seqretry(&my_seq_lock, seq));
	printk("seq_lock_func- read seq:%d\n", seq);
}

struct mutex my_mutex;

static void mutex_lock_func(void) {
	mutex_init(&my_mutex);
	mutex_lock(&my_mutex);
	printk("mutex_lock_func- init lock unlock\n");
	mutex_unlock(&my_mutex);
}

rwlock_t my_rwlock;

static void rwlock_lock_func(void) {
	rwlock_init(&my_rwlock);
	read_lock(&my_rwlock);
	printk("rwlock_lock_func- init read lock unlock\n");
	read_unlock(&my_rwlock);
	write_lock(&my_rwlock);
	printk("rwlock_lock_func- init write lock unlock\n");
	write_unlock(&my_rwlock);
}

static void rcu_lock_func(void) {
	rcu_read_lock_sched();
	printk("rcu_lock_func- init lock unlock\n");
	rcu_read_unlock_sched();
}

struct semaphore my_sem;

static void semaphore_func(void) {
	sema_init(&my_sem, 2);
	down(&my_sem);
	printk("semaphore_lock_func- init lock unlock\n");
	up(&my_sem);
}

struct rw_semaphore my_rwsem;

static void rwsemaphore_func(void) {
	init_rwsem(&my_rwsem);
	down_read(&my_rwsem);
	printk("rwsemaphore_lock_func- read lock unlock\n");
	up_read(&my_rwsem);
	down_write(&my_rwsem);
	printk("rwsemaphore_lock_func- write lock unlock\n");
	up_write(&my_rwsem);
}

struct completion my_completion;
struct timer_list timer1;

void timer_func(unsigned long data) {
	struct timer_list *data_ptr = (struct timer_list *) data;
	printk("timer_func data:%lu, expires:%lu\n", data, data_ptr->expires);
	printk("timer_func process %i (%s) awakening the readers\n",
		current->pid, current->comm);
	complete(&my_completion);
}

static void add_timer_func(struct timer_list *timer) {
	init_timer(timer);
	timer->data = (unsigned long)timer;
	timer->function = timer_func;
	timer->expires = jiffies + 10000;
	add_timer(timer);
}


static void completion_func(void) {
	init_completion(&my_completion);
	add_timer_func(&timer1);
	printk("completion_func %i (%s) going to sleep\n",
		current->pid, current->comm);
	wait_for_completion(&my_completion);
	printk("completion_func, awoken %i (%s)\n",
		current->pid, current->comm);
}
static int hello_init(void)
{
	printk(KERN_ERR"Module, hello lock.\n");
	spin_lock_func();
	seq_lock_func();
	mutex_lock_func();
	rwlock_lock_func();
	rcu_lock_func();
	semaphore_func();
	rwsemaphore_func();
	completion_func();
	return 0x0;
}

static void hello_exit(void)
{
	printk(KERN_ERR"Module, hello exit.\n");
	return;
}
module_init(hello_init);
module_exit(hello_exit);
