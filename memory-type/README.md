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

<3>[44051.218432] Module, hello memory.
<4>[44051.218941] kmalloc buf ptr:18446612134042508160, data:XXXXXXXXXX
<4>[44051.218947] vmalloc buf ptr:18446683600573865984, data:XXXXXXXXXX
<4>[44051.218949] ioremap buf ptr:18446612132314218496, data:XXXXXXXXXX
<4>[44051.218951] ioread8:31
<4>[44051.218952] ioread16:3233
<4>[44051.218953] ioread32:3435
<4>[44051.218954] get_free_page ptr:18446612134371426304, data:XXXXXXXXXX
<4>[44051.218956] get_zeroed_page ptr:18446612134371426304, data:XXXXXXXXXX
<3>[44052.810079] Module, hello exit.
```
