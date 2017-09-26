Step of building
-----
```bash
make
```
	hello.ko will be compiled.
## insert module to kernel module list
	insmod hello.ko
## list module list.
	lsmod
```bash
Module                  Size  Used by
hello                  12496  0
```
## to display module infos
	modinfo hello.ko
```bash
filename:       /root/kernel/hello/hello.ko
license:        Dual BSD/GPL
author:         voipman
rhelversion:    7.3
srcversion:     281BF8C84B384FC871B43A6
depends:
vermagic:       3.10.0-514.26.2.el7.x86_64 SMP mod_unload modversions
```
## remove module from kernel.
	rmmod hello.ko
## kernel message
```bash
cat /proc/kmsg
<3>[111315.139126] Module, hello world.
<3>[111382.817777] Module, hello exit.
```
