Step of building
-----
```bash
make
```
	hello-lock.ko will be compiled.
## insert module to kernel module list
	insmod hello-lock.ko
## remove module from kernel.
	rmmod hello-lock.ko
## kernel message
```bash
cat /proc/kmsg
<3>[65302.909365] Module, hello lock.
<4>[65302.909460] spin_lock_func-spin_lock init lock unlock
<4>[65302.909461] seq_lock_func- wirte_seq_lock/unlock
<4>[65302.909462] seq_lock_func- read seq:2
<4>[65302.909463] mutex_lock_func- init lock unlock
<4>[65302.909463] rwlock_lock_func- init read lock unlock
<4>[65302.909464] rwlock_lock_func- init write lock unlock
<4>[65302.909465] rcu_lock_func- init lock unlock
<4>[65302.909465] semaphore_lock_func- init lock unlock
<4>[65302.909466] rwsemaphore_lock_func- read lock unlock
<4>[65302.909467] rwsemaphore_lock_func- write lock unlock
<4>[65302.909468] completion_func 7545 (insmod) going to sleep
<4>[65312.921012] timer_func data:18446744072103576128, expires:4307508192
<4>[65312.921038] timer_func process 0 (swapper/0) awakening the readers
<4>[65312.921170] completion_func, awoken 7545 (insmod)
<3>[65321.736393] Module, hello exit.
```
