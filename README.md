Linux Device Driver
========

This project is demo of linux device driver. It provides driver of charactor driver, block driver and net driver.

**NOTE**: This is a Work-In-Progress. A lot of will change in the coming weeks, and I recommend against using this in production code as API might change. Patches are welcome!

list-type
------------
	test code of list_head, list_add, list_add_tail, list_del, list_move, list_move_tail and list_for_each.
	
kfifo-type
------------
	test code of kfifo_alloc, kfifo_in, kfifo_out, kfifo_size, kfifo_len, kfifo_avail, kfifo_is_empty, kfifo_is_full, kfifo_reset, kfifo_free.
	
Charactor Driver
------------

	implement of charactor driver.

|System V API | hello-driver function|
|----|----|
| open| hello_open|
| read| hello_read|
| write|hello_write|
| ioctl | hello_ioctl|
| close|hello_close|
| poll|hello_poll|

Block Driver
-------------

	implement of block  driver.



Net Driver
-------------

TBD


LICENSE
-------

This project is under Apache License, Version 2.0. For more details please see LICENSE file.

Copyright
---------

Copyright (C)  2017 Wang Yaofu. All rights reserved.
