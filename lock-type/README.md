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
<3>[62426.809478] Module, hello lock.
<4>[62426.809601] spin_lock_func-spin_lock init lock unlock
<4>[62426.809602] seq_lock_func- wirte_seq_lock/unlock
<4>[62426.809603] seq_lock_func- read seq:2
<4>[62426.809604] mutex_lock_func- init lock unlock
<4>[62426.809605] rwlock_lock_func- init read lock unlock
<4>[62426.809606] rwlock_lock_func- init write lock unlock
<3>[62436.548528] Module, hello exit.
```
