Step of building
-----
```bash
make
```
	hello-timer.ko will be compiled.
## insert module to kernel module list
	insmod hello-timer.ko
## list module list.
	lsmod
```bash
Module                  Size  Used by
hello_timer            12694  0
```
## to display module infos
	modinfo hello-timer.ko
```bash
filename:       /root/kernel/ldd/timer-type/hello-timer.ko
license:        Dual BSD/GPL
author:         voipman
srcversion:     F4B8F0326FC5468934D816A
depends:
vermagic:       3.10.0-123.el7.x86_64 SMP mod_unload modversions
```
## remove module from kernel.
	rmmod hello-timer.ko
## kernel message
```bash
cat /proc/kmsg

<3>[31998.673195] Module, hello timer.
<4>[31998.673490] timer_demo init_timer
<4>[31998.687749] timer_func data:18446744072103625568, expires:4294921532
<4>[31998.791704] timer_func data:18446744072103625472, expires:4294921634
<4>[31998.876155] after add_timer
<4>[31998.876158] after del_timer
<4>[31998.884932] timer_func data:18446744072103625280, expires:4294921734
<3>[32001.164856] Module, hello timer exit.
```
