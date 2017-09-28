#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/vmalloc.h>
#include <linux/hdreg.h>
#include <linux/blkdev.h>
#include <linux/blkpg.h>
#include <asm/uaccess.h>

#define HELLO_BLK_DEV_NAME "hello_blk" /* block device name */
#define HELLO_BLK_DEV_MAJOR 220        /* block device major */
#define HELLO_BLK_MAX_DEVICE 2         /* block max device number */
#define HELLO_BLOCKSIZE   1024
#define HELLO_BLK_SECTOR_SIZE 512      /* block sector size, default 512*/
#define HELLO_BLK_SIZE (4*1024*1024)   /* block max size 4Mb */
#define HELLO_BLK_SECTOR_TOTAL (HELLO_BLK_SIZE/HELLO_BLK_SECTOR_SIZE)  /* count of sector*/

typedef struct
{
    unsigned char *data;
    struct request_queue *queue;
    struct gendisk *gd;
}hello_blk_device;

/* disk */
static char *vdisk[HELLO_BLK_MAX_DEVICE];

static hello_blk_device device[HELLO_BLK_MAX_DEVICE];

/* block request function of the block */
static void hello_blk_make_request(struct request_queue *q, struct bio *bio)
{
    hello_blk_device *pdevice;    
    char *pdevice_data;
    char *pdevice_buffer;
    struct bio_vec *bvec;
    int i;
       
    printk("Module, hello block hello_blk_make_request.\n");
    printk("Module, bio.sector:%d, bio.size:%d.\n", bio->bi_sector, bio->bi_size);

    if(((bio->bi_sector*HELLO_BLK_SECTOR_SIZE) + bio->bi_size) > HELLO_BLK_SIZE)
    {
        bio_io_error(bio/*, bio->bi_size*/);
        return;
    }
    else
    {        
        pdevice = (hello_blk_device *) bio->bi_bdev->bd_disk->private_data;
        pdevice_data = pdevice->data + (bio-> bi_sector*HELLO_BLK_SECTOR_SIZE);
        
        bio_for_each_segment(bvec, bio, i)
        {            
            pdevice_buffer = kmap(bvec->bv_page) + bvec-> bv_offset;
            
            switch(bio_data_dir(bio))
            {
                case READA :    
                case READ : 
 	            memcpy(pdevice_buffer, pdevice_data, bvec->bv_len);
		    break;
                case WRITE :
                    memcpy(pdevice_data, pdevice_buffer, bvec->bv_len);
                    break;
                default : kunmap(bvec->bv_page);
                    bio_io_error(bio);
                    return;            
            }
            
            kunmap(bvec->bv_page);
            pdevice_data += bvec->bv_len;
        }
        /* stop hello_blk_make_request */
        bio_endio(bio, /*bio->bi_size, */0);
        return;
    }    
}

int hello_blk_open(struct inode *inode, struct file *filp)
{
    printk("Module, hello block open.\n");
    return 0;
}

int hello_blk_release (struct inode *inode, struct file *filp)
{
    printk("Module, hello block release.\n");
    return 0;
}

int hello_blk_ioctl(struct inode *inode, struct file *filp, unsigned int cmd,unsigned long arg)
{
    int error;
    struct block_device *bdev = inode->i_bdev;
    if(cmd!= BLKFLSBUF)
    {
        return -ENOTTY;//不适当的I/O控制操作（没有tty终端）
    }
    error = -EBUSY;//资源正忙

    if(bdev->bd_openers <= 2)
    {
        truncate_inode_pages(bdev->bd_inode->i_mapping,0);
        error = 0;
    }

    return error;
}

/* block_device_operations */
static struct block_device_operations vrd_fops =
{
    .owner = THIS_MODULE,
    .open = hello_blk_open,
    .release = hello_blk_release,
    .ioctl = hello_blk_ioctl,
};

int hello_blk_init(void)
{
    int i;    
    int err = -ENOMEM;
    printk("Module, hello block init.\n");

    for(i=0; i < HELLO_BLK_MAX_DEVICE; i++)
    {
        vdisk[i] = vmalloc(HELLO_BLK_SIZE);
    } 
    
    /* register block device */ 
    if(register_blkdev(HELLO_BLK_DEV_MAJOR, HELLO_BLK_DEV_NAME))
    {
        err = -EIO;
            goto out;
    }

    /**/
    for(i = 0; i < HELLO_BLK_MAX_DEVICE; i++)
    {
        device[i].data = vdisk[i];    
        /* alloc gendisk*/
        device[i].gd = alloc_disk(1);

        if (!device[i].gd) goto out;

        device[i].queue = blk_alloc_queue(GFP_KERNEL);
        if (!device[i].queue)
        {
                put_disk(device[i].gd);
                goto out;
        }
        /* to set block queue request function */
        blk_queue_make_request(device[i].queue, &hello_blk_make_request);
        blk_queue_logical_block_size(device[i].queue,HELLO_BLOCKSIZE);/* block size */

        device[i].gd->major = HELLO_BLK_DEV_MAJOR;
        device[i].gd->first_minor = i;
        device[i].gd->fops = &vrd_fops;
        device[i].gd->queue = device[i].queue;
        device[i].gd->private_data = &device[i];
        sprintf(device[i].gd->disk_name, "hello_blk%c" , 'a'+i);//
        set_capacity(device[i].gd,HELLO_BLK_SECTOR_TOTAL);
        
        add_disk(device[i].gd);
    }

    printk("RAMDISK driver initialized!\n");
    return 0;
out:
   while (i--) {
       put_disk(device[i].gd);
       blk_cleanup_queue(device[i].queue);
   }
   return err;
}

void hello_blk_exit(void)
{
    printk("Module, hello block exit.\n");
    int i;    
    for(i = 0; i < HELLO_BLK_MAX_DEVICE; i++)
    {
        /*delete gendisk struct*/
        del_gendisk(device[i].gd);
        /*decrease gendisk struct reference */
        put_disk(device[i].gd);
        blk_cleanup_queue(device[i].queue);
    }
    unregister_blkdev(HELLO_BLK_DEV_MAJOR, HELLO_BLK_DEV_NAME);
    for(i=0;i < HELLO_BLK_MAX_DEVICE; i++)
    {
        vfree(vdisk[i]);
    }
}

module_init(hello_blk_init);
module_exit(hello_blk_exit);

MODULE_AUTHOR("voipman");
MODULE_LICENSE("Dual BSD/GPL");
