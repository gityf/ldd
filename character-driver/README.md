Step of building
-----
```bash
make
```
	hello-ch.ko will be compiled.
## insert module to kernel module list
	insmod hello-ch.ko
## list module list.
	lsmod
```bash
Module                  Size  Used by
hello-ch                12743      0
```
## to display module infos
	modinfo hello-ch.ko
```bash
filename:       /root/kernel/ch_driver/hello-ch.ko
license:        Dual BSD/GPL
author:         voipman
rhelversion:    7.3
srcversion:     679F332878D8773EBD75978
depends:
vermagic:       3.10.0-514.26.2.el7.x86_64 SMP mod_unload modversions
```
## remove module from kernel.
	rmmod hello-ch.ko
## kernel message
```bash
cat /proc/kmsg
<5>[116825.709965] hello init: 249, 0
<5>[116844.742880] Hello device open!
<5>[116844.742912] hello: user read 10 bytes from me. KKKKKKKKKK
<5>[116844.742921] hello: user has written 6 bytes to me: Hello
<5>[116844.742924] Hello device close!
```
## access /dev/hello0 device
```bash
./test-ch /dev/hello0 c 10 0
/dev/hello0 has been opened: (fd:3).
read 10 bytes from /dev/hello0:KKKKKKKKKK@
write 6 bytes to /dev/hello0:Hello
close device /dev/hello0
```
