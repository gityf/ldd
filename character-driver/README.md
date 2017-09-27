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
filename:       /root/kernel/ldd/character-driver/hello-ch.ko
license:        Dual BSD/GPL
author:         voipman
srcversion:     458978AA364981249766112
depends:
vermagic:       3.10.0-123.el7.x86_64 SMP mod_unload modversions
```
## get device id
	cat /prod/device | grep hello
	249 hello
## make device node
	mknod /dev/hello0 c 249 0
	ls /dev/hello0
	/dev/hello0
## test and access /dev/hello0 device
```bash
./test-ch /dev/hello0 c 10 0
/dev/hello0 has been opened: (fd:3).
read 10 bytes from /dev/hello0:KKKKKKKKKK@
write 6 bytes to /dev/hello0:Hello
close device /dev/hello0
```
## remove module from kernel.
	rmmod hello-ch.ko
## kernel message
```bash
cat /proc/kmsg
<5>[36307.113583] hello init: 249, 0
<5>[36597.563243] Hello device open!
<5>[36597.563290] hello: user read 10 bytes from me. KKKKKKKKKK
<5>[36597.563301] hello: user has written 6 bytes to me: Hello
<5>[36597.563305] Hello device close!
<5>[36642.041990] hello exit. major:249,minor 0
```
