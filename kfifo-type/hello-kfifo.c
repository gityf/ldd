#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/slab.h>         /* kmalloc()kfree() */
#include <asm/io.h>
#include <linux/kernel.h>	/* printk() */
#include <linux/kfifo.h>        /* kfifo */
#include <linux/fs.h>	   
#include <linux/poll.h>	        /* poll() */ 
#include <linux/errno.h>	/* error codes */
#include <linux/types.h>	/* size_t */
#include <linux/cdev.h>
#include <linux/mutex.h>
#include <asm/uaccess.h>	/* copy_to_user() */

#include "ioc-fifo-cmd.h"       /* ioc command */

#define  HELLO_KFIFO_SIZE (1024 * 1024)
static struct kfifo hello_fifo;

/* lock for read access */  
static DEFINE_MUTEX(r_lock);  
/* lock for write access */  
static DEFINE_MUTEX(w_lock); 

/* function prototypes */
static int hello_open(struct inode *inode, struct file *filp);
static int hello_release(struct inode *inode, struct file *filp);
ssize_t hello_read(struct file *flip, char __user *buf, size_t count,loff_t
					*f_pos);
ssize_t hello_write(struct file *filp, const char __user *buf, size_t count,
					 loff_t *f_pos);
ssize_t hello_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);
unsigned int hello_poll(struct file *filp, struct poll_table_struct *ptable);

static int hello_major = 0;		/* major device number */
MODULE_AUTHOR( "voipman" );
MODULE_LICENSE( "Dual BSD/GPL" );

static struct cdev helloDev;	/* hello device structure */

/* file operations for hello device */
static struct file_operations hello_ops = {
	.owner = THIS_MODULE,
	.open = hello_open,
	.read = hello_read,
	.write = hello_write,
        .unlocked_ioctl = hello_ioctl,
	.release = hello_release,
};
/* Open the device */
static int hello_open( struct inode *inode, struct file *filp ){
	printk( KERN_NOTICE"Hello kfifo device open!\n" );
	return 0;
}

/* Close hello_device */
static int hello_release( struct inode *inode, struct file *filp ){
	printk( KERN_NOTICE"Hello kfifo device close!\n" );
	return 0;
}

/* set up the cdev stucture for a device */
static void hello_setup_cdev( struct cdev *dev, int minor, struct
file_operations *fops ){
	int err;
	int devno = MKDEV( hello_major, minor );
	/* initialize the cdev struct */
	cdev_init( dev,fops );
	dev->owner = THIS_MODULE;
	dev->ops = fops;				 /* why not do it in cdev_init ? */
	err = cdev_add( dev, devno, 1 ); /* register the cdev in the kernel */
	if( err )
		printk( KERN_NOTICE"Error %d adding hello%d\n",err ,minor );
}

/* Module housekeeping */
static int hello_init(void){
	int result;
	dev_t dev = MKDEV( hello_major, 0 );

        result = kfifo_alloc(&hello_fifo, HELLO_KFIFO_SIZE, GFP_KERNEL);
	if( result < 0 ){
		printk( KERN_NOTICE"Hello: unable to kfifo_alloc:%d\n",hello_major );
		return result;
	}

	/* alloc the major device number dynamicly */
	result = alloc_chrdev_region(&dev, 0 ,1, "hello-kfifo" );
	if( result < 0 ){
		printk( KERN_NOTICE"Hello: unable to get major %d\n",hello_major );
		return result;
	}
	hello_major = MAJOR(dev);
	/* set up devices, in this case, there is only one device */
	printk( KERN_NOTICE"hello init: %d, %d\n",hello_major,0 );
	hello_setup_cdev(&helloDev, 0 , &hello_ops );
	
	return 0;
	
}

/* Exit routine */
static void hello_exit(void){
        kfifo_free(&hello_fifo);
        /* remove the cdev from kernel */
	cdev_del(&helloDev );
	/* release the device numble alloced earlier */
	unregister_chrdev_region( MKDEV( hello_major, 0 ), 1 );
	printk( KERN_NOTICE"hello exit. major:%d,minor %d\n",hello_major,0 );
}

/* user read from hello device*/
ssize_t hello_read( struct file *flip, char __user *buf, size_t count,loff_t
					*f_pos){
        ssize_t copied = 0;

        if (mutex_lock_interruptible(&r_lock))  
            return -ERESTARTSYS;
        kfifo_to_user(&hello_fifo, buf, count, &copied);
	printk( KERN_NOTICE"hello: user read %d bytes from kfifo, data:[%s]\n", copied, buf);
        mutex_unlock(&r_lock);
	return copied;
}

/* write to hello device */
ssize_t hello_write( struct file *filp, const char __user *buf, size_t count,
					 loff_t *f_pos ){
	ssize_t copied = 0;

        if (mutex_lock_interruptible(&w_lock))  
            return -ERESTARTSYS;
        kfifo_from_user(&hello_fifo, buf, count, &copied);
	printk( KERN_NOTICE"hello: user has written %d bytes to kfifo, data:[%s]\n",copied,
			buf);
        mutex_unlock(&w_lock);  
	return copied;
}

/* ioctl to kernel device */
ssize_t hello_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{

    int err = 0;
    int ret = 0;
    unsigned int ioarg = 0;
    char *bank;
    int count = 20;
    
    /* to check magic is CH_DEV_IOC_MAGIC or not*/
    if (_IOC_TYPE(cmd) != CH_DEV_IOC_MAGIC) 
        return -EINVAL;
    /* when the cmd is large then CH_DEV_IOC_MAXNR, err */
    if (_IOC_NR(cmd) > CH_DEV_IOC_MAXNR) 
        return -EINVAL;

    /* to check user space of arg access ok or not */
    if (_IOC_DIR(cmd) & _IOC_READ)
        err = !access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd));
    else if (_IOC_DIR(cmd) & _IOC_WRITE)
        err = !access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd));
    if (err) {
        printk(KERN_ERR"hello-device: arg address access err");
        return -EFAULT;
    }

    switch(cmd) {
      case CH_DEV_IOC_PRINT:
          printk(KERN_NOTICE"hello-device: CMD CH_DEV_IOC_PRINT Done\n");
        break;
      
      case CH_DEV_IOC_GET_FIFO_SIZE: 
        ioarg = kfifo_size(&hello_fifo);
        ret = __put_user(ioarg, (int *)arg);
        printk(KERN_NOTICE"hello-device: kfifo_size ioarg = %d \n", ioarg);
        break;
      
      case CH_DEV_IOC_GET_FIFO_LEN: 
        ioarg = kfifo_len(&hello_fifo);
        ret = __put_user(ioarg, (int *)arg);
        printk(KERN_NOTICE"hello-device: kfifo_len ioarg = %d \n", ioarg);
        break;

      case CH_DEV_IOC_GET_FIFO_AVAIL: 
        ioarg = kfifo_avail(&hello_fifo);
        ret = __put_user(ioarg, (int *)arg);
        printk(KERN_NOTICE"hello-device: kfifo_avoil ioarg = %d \n", ioarg);
        break;
      
      case CH_DEV_IOC_GET_FIFO_IS_EMPTY: 
        ioarg = kfifo_is_empty(&hello_fifo);
        ret = __put_user(ioarg, (int *)arg);
        printk(KERN_NOTICE"hello-device: kfifo_is_empty ioarg = %d \n", ioarg);
        break;
      
      case CH_DEV_IOC_GET_FIFO_IS_FULL: 
        ioarg = kfifo_is_full(&hello_fifo);
        ret = __put_user(ioarg, (int *)arg);
        printk(KERN_NOTICE"hello-device: kfifo_is_full ioarg = %d \n", ioarg);
        break;
      
      case CH_DEV_IOC_GET_FIFO_RESET: 
        kfifo_reset(&hello_fifo);
        printk(KERN_NOTICE"hello-device: kfifo_reset \n");
        break;
      
      case CH_DEV_IOC_FIFO_INDATA: 
	bank = kmalloc(count+1 ,GFP_KERNEL );
	if (bank == NULL)
		return -EFAULT;
	if (copy_from_user(bank, (char *)arg, count)){
		printk( KERN_NOTICE"hello: CH_DEV_IOC_FIFO_INDATA error\n" );
		return -EFAULT;
	}
        printk(KERN_NOTICE"hello-device: In Kernel CH_DEV_IOC_FIFO_INDATA arg = %s \n", bank);
	kfree(bank);
        break;

      default:  
        return -EINVAL;
    }
    return ret;
}

/* register the init and exit routine of the module */
module_init( hello_init );
module_exit( hello_exit );
