CURR_PATH   = $(shell pwd)
KERNEL_PATH = /usr/src/kernels/3.10.0-123.el7.x86_64
BUILD_PATH  = $(CURR_PATH)/build 
obj-m := hello.o
default:
	make -C $(KERNEL_PATH) M=$(CURR_PATH) modules
.PHONY:clean
clean:
	@$(RM) *.o *.ko *.mod.* Module.*
