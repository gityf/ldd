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
read 20 bytes from /dev/hello0:KKKKKKKKKKKKKKKKKKKK
write 6 bytes to /dev/hello0:Hello
Call CCH_DEV_IOC_PRINT
Call CH_DEV_IOC_SETDATA
Call CH_DEV_IOC_GETDATA
In User Space CH_DEV_IOC_GETDATA Get Data is 20170910
Call CH_DEV_IOC_GETBUFDATA
In User Space CH_DEV_IOC_GETBUFDATA Get Data is BBBBBBBBBBBBBBBBBBBB
Call CH_DEV_IOC_SETBUFDATA
In User Space CH_DEV_IOC_SETBUFDATA Set Data is UUUUUUUUUUUUUUUUUUUU
close device /dev/hello0
```
## remove module from kernel.
	rmmod hello-ch.ko
## kernel message
```bash
cat /proc/kmsg

<5>[45543.623376] hello init: 249, 0
<5>[45548.559441] Hello device open!
<5>[45548.559449] hello: user read 20 bytes from me. KKKKKKKKKKKKKKKKKKKK
<5>[45548.559458] hello: user has written 6 bytes to me: Hello
<5>[45548.559466] hello-device: CMD CH_DEV_IOC_PRINT Done
<5>[45548.559469] hello-device: In Kernel CH_DEV_IOC_SETDATA ioarg = 20170909
<5>[45548.559474] hello-device: In Kernel CH_DEV_IOC_GETBUFDATA arg = BBBBBBBBBBBBBBBBBBBB
<5>[45548.559478] hello-device: In Kernel CH_DEV_IOC_SETBUFDATA arg = UUUUUUUUUUUUUUUUUUUU
<5>[45548.559481] Hello device close!
<5>[45562.744405] hello exit. major:249,minor 0
```
