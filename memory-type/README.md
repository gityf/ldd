Step of building
-----
```bash
make
```
	hello-mem.ko will be compiled.
## insert module to kernel module list
	insmod hello-mem.ko
## list module list.
	lsmod
```bash
Module                  Size  Used by
hello                  12496  0
```
## to display module infos
	modinfo hello-mem.ko
```bash
filename:       /root/kernel/ldd/memory-type/hello-mem.ko
license:        Dual BSD/GPL
author:         voipman
srcversion:     E685C29D55B8D4A5F8637A3
depends:
vermagic:       3.10.0-123.el7.x86_64 SMP mod_unload modversions
```
## remove module from kernel.
	rmmod hello-mem.ko
## kernel message
```bash
cat /proc/kmsg

<3>[69169.551934] Module, hello exit.
<3>[69170.840443] Module, hello memory.
<4>[69170.840571] kmalloc buf ptr:18446612134365688000, data:XXXXXXXXXX
<4>[69170.840576] vmalloc buf ptr:18446683600573865984, data:XXXXXXXXXX
<4>[69170.840578] ioremap buf ptr:18446612132314218496, data:XXXXXXXXXX
<4>[69170.840579] ioread8:31
<4>[69170.840580] ioread16:3233
<4>[69170.840581] ioread32:3435
<4>[69170.840583] get_free_page ptr:18446612134056284160, data:XXXXXXXXXX
<4>[69170.840584] get_zeroed_page ptr:18446612134056284160, data:XXXXXXXXXX
<4>[69170.840607] kmem_cache_alloc buf ptr:18446612134050163072, data:FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
<4>[69170.840611] mempool_alloc buf ptr:18446612134058848128, data:FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
<3>[69172.455729] Module, hello exit.
```
