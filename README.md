Linux Device Driver
========

This project is demo of linux device driver. It provides driver of charactor driver, block driver and net driver.

**NOTE**: This is a Work-In-Progress. A lot of will change in the coming weeks, and I recommend against using this in production code as API might change. Patches are welcome!

Charactor Driver
------------

	implement of charactor driver.
	|----|----|
        |System V API | hello-driver function|
        | open| hello_open|
        | read| hello_read|
        | write|hello_write|
        | ioctl | hello_ioctl|
        | close|ioctl_close|
        |----|----|

Block Driver
-------------

TBD


Net Driver
-------------

TBD


LICENSE
-------

This project is under Apache License, Version 2.0. For more details please see LICENSE file.

Copyright
---------

Copyright (C)  2017 Wang Yaofu. All rights reserved.
