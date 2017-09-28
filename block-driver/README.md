Step of building
-----
```bash
make
```
	hello-blk.ko will be compiled.
## insert module to kernel module list
	insmod hello-blk.ko
## list module list.
	lsmod
```bash
Module                  Size  Used by
hello-blk               12766      0
```
## to display module infos
	modinfo hello-blk.ko
```bash
filename:       /root/kernel/ldd/block-driver/hello-blk.ko
license:        Dual BSD/GPL
author:         voipman
srcversion:     91A07BCCFDDFF70CD079EA2
depends:
vermagic:       3.10.0-123.el7.x86_64 SMP mod_unload modversions
```
## get device id
	cat /prod/device | grep hello
	220 hello_blk
## make device node
	mknod /dev/hello-blk0 b 220 0
## make block device to fs as ext3 format.
[root@localhost block-driver]# mkfs.ext3 /dev/hello-blk0
mke2fs 1.42.9 (28-Dec-2013)
Filesystem label=
OS type: Linux
Block size=1024 (log=0)
Fragment size=1024 (log=0)
Stride=0 blocks, Stripe width=0 blocks
1024 inodes, 4096 blocks
204 blocks (4.98%) reserved for the super user
First data block=1
blk
Maximum filesystem blocks=4194304
1 block group
8192 blocks per group, 8192 fragments per group
1024 inodes per group

Allocating group tables: done
Writing inode tables: done
Creating journal (1024 blocks): done
Writing superblocks and filesystem accounting information: done
```
## list the device of hello-blk after mkfs.ext3
```bash
[root@localhost blk]# ls -l /dev/hello*
brw-r--r--. 1 root root 220, 0 Sep 28 20:47 /dev/hello-blk0
brw-rw----. 1 root disk 220, 0 Sep 28 20:42 /dev/hello_blka
brw-rw----. 1 root disk 220, 1 Sep 28 20:42 /dev/hello_blkb
```
## mount the device and list device.
	mount /dev/hello-blk0 /ldd/blk/
```bash
[root@localhost blk]# df -h |grep hello
/dev/hello-blk0          2.9M   34K  2.6M   2% /ldd/blk
```
## to access directory /ldd/blk 
## remove module from kernel.
	rmmod hello-blk.ko
## kernel message
```bash
cat /proc/kmsg

<4>[97320.068664] Module, hello block init.
<4>[97238.011267] RAMDISK driver initialized!
<4>[97320.071054] RAMDISK driver initialized!Module, hello block open.
<4>[97320.073676] Module, hello block open.
<4>[97320.073949] Module, hello block release.
<4>[97320.074436] Module, hello block release.
<4>[97320.076537] Module, hello block open.
<4>[97320.076849] Module, hello block open.
<4>[97320.077103] Module, hello block release.
<4>[97320.077601] Module, hello block release.
<4>[97567.109932] Module, hello block open.
<4>[97567.109938] Module, hello block release.
<4>[97567.109946] Module, hello block open.
<4>[97567.109951] Module, hello block release.
<4>[97567.109984] Module, hello block open.
<4>[97567.109986] Module, hello block release.
<4>[97567.109989] Module, hello block open.
<4>[97567.109990] Module, hello block release.
<4>[97567.110002] Module, hello block open.
<4>[97567.110200] Module, hello block release.
<4>[97567.110234] Module, hello block open.
<4>[97567.111973] Module, hello block release.
<4>[97601.938446] Module, hello block open.
<4>[97601.938753] Module, hello block release.
<4>[97601.938800] Module, hello block open.
<6>[97601.938812] EXT4-fs (hello_blka): mounting ext3 file system using the ext4 subsystem
<6>[97601.942856] EXT4-fs (hello_blka): mounted filesystem with ordered data mode. Opts: (null)
<7>[97601.942867] SELinux: initialized (dev hello_blka, type ext3), uses xattr
<4>[97945.391326] Module, hello block release.
<4>[97947.262421] Module, hello block exit.
```
