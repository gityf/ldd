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
<3>[63557.645019] Module, hello lock.
<4>[63557.645139] spin_lock_func-spin_lock init lock unlock
<4>[63557.645140] seq_lock_func- wirte_seq_lock/unlock
<4>[63557.645141] seq_lock_func- read seq:2
<4>[63557.645142] mutex_lock_func- init lock unlock
<4>[63557.645143] rwlock_lock_func- init read lock unlock
<4>[63557.645144] rwlock_lock_func- init write lock unlock
<4>[63557.645145] rcu_lock_func- init lock unlock
<4>[63557.645146] semaphore_lock_func- init lock unlock
<3>[63563.667118] Module, hello exit.
```
