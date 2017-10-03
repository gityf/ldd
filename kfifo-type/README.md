Step of building
-----
```bash
make
```
	hello-kfifo.ko will be compiled.
## insert module to kernel module list
	insmod hello-kfifo.ko
## list module list.
	lsmod
```bash
Module                  Size  Used by
hello-kfifo                12743      0
```
## to display module infos
	modinfo hello-kfifo.ko
```bash

filename:       /root/kernel/ldd/kfifo-type/hello-kfifo.ko
license:        Dual BSD/GPL
author:         voipman
srcversion:     F28C1D582E05A30A00FA47B
depends:
vermagic:       3.10.0-123.el7.x86_64 SMP mod_unload modversions
```
## get device id
	cat /prod/device | grep hello
	249 hello-kfifo
## make device node
	mknod /dev/hello0 c 249 0
	ls /dev/hello0
	/dev/hello0
## test and access /dev/hello0 device
```bash
./test-fifo /dev/hello0

[root@localhost kfifo-type]# ./test-fifo /dev/hello0
/dev/hello0 has been opened: (fd:3).
read 0 bytes from /dev/hello0:À
@
write 6 bytes to /dev/hello0:Hello
Call CCH_DEV_IOC_PRINT
Call CH_DEV_IOC_GET_FIFO_SIZE
In User Space kfifo size: 1048576
Call CH_DEV_IOC_GET_FIFO_LEN
In User Space kfifo data len: 6
Call CH_DEV_IOC_GET_FIFO_AVAIL
In User Space kfifo avail size: 1048570
close device /dev/hello0
[root@localhost kfifo-type]# ./test-fifo /dev/hello0
/dev/hello0 has been opened: (fd:3).
read 6 bytes from /dev/hello0:Hello
write 6 bytes to /dev/hello0:Hello
Call CCH_DEV_IOC_PRINT
Call CH_DEV_IOC_GET_FIFO_SIZE
In User Space kfifo size: 1048576
Call CH_DEV_IOC_GET_FIFO_LEN
In User Space kfifo data len: 6
Call CH_DEV_IOC_GET_FIFO_AVAIL
In User Space kfifo avail size: 1048570
close device /dev/hello0
```
## remove module from kernel.
	rmmod hello-kfifo.ko
## kernel message
```bash
cat /proc/kmsg

<5>[ 8894.604690] Hello kfifo device open!
<5>[ 8894.604720] hello: user read 0 bytes from kfifo, data:[À
<5>[ 8894.604720] @]
<5>[ 8894.604731] hello: user has written 6 bytes to kfifo, data:[Hello]
<5>[ 8894.604739] hello-device: CMD CH_DEV_IOC_PRINT Done
<5>[ 8894.604742] hello-device: kfifo_size ioarg = 1048576
<5>[ 8894.604745] hello-device: kfifo_len ioarg = 6
<5>[ 8894.604749] hello-device: kfifo_avoil ioarg = 1048570
<5>[ 8894.604752] Hello kfifo device close!
<5>[ 8921.423798] Hello kfifo device open!
<5>[ 8921.423830] hello: user read 6 bytes from kfifo, data:[Hello]
<5>[ 8921.423840] hello: user has written 6 bytes to kfifo, data:[Hello]
<5>[ 8921.423848] hello-device: CMD CH_DEV_IOC_PRINT Done
<5>[ 8921.423851] hello-device: kfifo_size ioarg = 1048576
<5>[ 8921.423855] hello-device: kfifo_len ioarg = 6
<5>[ 8921.423859] hello-device: kfifo_avoil ioarg = 1048570
<5>[ 8921.423863] Hello kfifo device close!
<5>[ 8940.102207] hello exit. major:249,minor 0
```
