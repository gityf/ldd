#include <linux/init.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/seqlock.h>
#include <linux/mutex.h>
#include <linux/rcupdate.h>
#include <linux/semaphore.h>

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

struct semaphore my_semaphore;

static void semaphore_func(void) {
	sema_init(&my_semaphore, 2);
	down(&my_semaphore);
	printk("semaphore_lock_func- init lock unlock\n");
	up(&my_semaphore);
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
	return 0x0;
}

static void hello_exit(void)
{
	printk(KERN_ERR"Module, hello exit.\n");
	return;
}
module_init(hello_init);
module_exit(hello_exit);
