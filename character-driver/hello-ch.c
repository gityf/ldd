#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/slab.h>         /* kmalloc()kfree() */
#include <asm/io.h>
#include <linux/kernel.h>	/* printk() */
#include <linux/fs.h>	   
#include <linux/poll.h>	        /* poll() */ 
#include <linux/errno.h>	/* error codes */
#include <linux/types.h>	/* size_t */
#include <linux/cdev.h>
#include <asm/uaccess.h>	/* copy_to_user() */

#include "ioc-cmd.h"            /* ioc command */

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
        .poll = hello_poll,
	.release = hello_release,
};
/* Open the device */
static int hello_open( struct inode *inode, struct file *filp ){
	printk( KERN_NOTICE"Hello device open!\n" );
	return 0;
}

/* Close hello_device */
static int hello_release( struct inode *inode, struct file *filp ){
	printk( KERN_NOTICE"Hello device close!\n" );
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

	/* alloc the major device number dynamicly */
	result = alloc_chrdev_region(&dev, 0 ,1, "hello" );
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
        /* remove the cdev from kernel */
	cdev_del(&helloDev );
	/* release the device numble alloced earlier */
	unregister_chrdev_region( MKDEV( hello_major, 0 ), 1 );
	printk( KERN_NOTICE"hello exit. major:%d,minor %d\n",hello_major,0 );
}

/* user read from hello device*/
ssize_t hello_read( struct file *flip, char __user *buf, size_t count,loff_t
					*f_pos){
	ssize_t retval = 0;
	char *bank;
	bank = (char *)kmalloc(count+1, GFP_KERNEL );
	if( bank == NULL )
		return -1;
	memset( bank, 'K',count );
        bank[count] = 0x00;
	if( copy_to_user( buf, bank, count+1 ) ){
		retval = -EFAULT;
		goto out;
	}
	retval += count;
	*(bank+count)=0;
	printk( KERN_NOTICE"hello: user read %d bytes from me. %s\n",(int)count,bank );
  out:
	kfree((void *)bank);
	return retval;
}

/* write to hello device */
ssize_t hello_write( struct file *filp, const char __user *buf, size_t count,
					 loff_t *f_pos ){
	ssize_t retval = 0;
	char *bank = kmalloc( count ,GFP_KERNEL );
	if( bank == NULL )
		return retval;
	if( copy_from_user(bank, buf, count ) ){
		retval = -EFAULT;
		printk( KERN_NOTICE"hello: write error\n" );
		goto out;
	}
	retval += count;
	printk( KERN_NOTICE"hello: user has written %d bytes to me: %s\n",count,
			bank );
  out:
	kfree(bank );
	return retval;
}

/* ioctl to kernel device */
ssize_t hello_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{

    int err = 0;
    int ret = 0;
    int ioarg = 0;
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
      
      case CH_DEV_IOC_GETDATA: 
        ioarg = 20170910;
        ret = __put_user(ioarg, (int *)arg);
        break;
      
      case CH_DEV_IOC_SETDATA: 
        ret = __get_user(ioarg, (int *)arg);
        printk(KERN_NOTICE"hello-device: In Kernel CH_DEV_IOC_SETDATA ioarg = %d \n", ioarg);
        break;

      case CH_DEV_IOC_GETBUFDATA: 
	bank = kmalloc(count ,GFP_KERNEL );
	if (bank == NULL)
		return -EFAULT;
        memset(bank, 'B', count);
        bank[count] = 0x00;
        
	if (copy_to_user((char *)arg, bank, count)){
		printk( KERN_NOTICE"hello: CH_DEV_IOC_SETBUFDATA error\n" );
		return -EFAULT;
	}
        printk(KERN_NOTICE"hello-device: In Kernel CH_DEV_IOC_GETBUFDATA arg = %s \n", bank);
	kfree(bank);
        break;
      
      case CH_DEV_IOC_SETBUFDATA: 
	bank = kmalloc(count+1 ,GFP_KERNEL );
	if (bank == NULL)
		return -EFAULT;
	if (copy_from_user(bank, (char *)arg, count)){
		printk( KERN_NOTICE"hello: CH_DEV_IOC_SETBUFDATA error\n" );
		return -EFAULT;
	}
        printk(KERN_NOTICE"hello-device: In Kernel CH_DEV_IOC_SETBUFDATA arg = %s \n", bank);
	kfree(bank);
        break;

      default:  
        return -EINVAL;
    }
    return ret;
}

unsigned int hello_poll(struct file *filp, struct poll_table_struct *ptable) {
    unsigned int mask = 0;
    printk(KERN_NOTICE"hello-device: In Kernel hello_poll call, return POLLIN");
    mask |= POLLIN; 
    return mask;
}
/* register the init and exit routine of the module */
module_init( hello_init );
module_exit( hello_exit );
