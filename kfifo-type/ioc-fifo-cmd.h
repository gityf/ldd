#ifndef _CH_DEV_IOC_FIFO_H
#define _CH_DEV_IOC_FIFO_H

#include <linux/ioctl.h>

/* to define magic number of the ioctl command */
#define CH_DEV_IOC_MAGIC  'V'

/* to define ioctl command */
#define CH_DEV_IOC_PRINT             _IO(CH_DEV_IOC_MAGIC, 1)
#define CH_DEV_IOC_GET_FIFO_SIZE     _IOW(CH_DEV_IOC_MAGIC, 2, int)
#define CH_DEV_IOC_GET_FIFO_LEN      _IOW(CH_DEV_IOC_MAGIC, 3, int)
#define CH_DEV_IOC_GET_FIFO_AVAIL    _IOW(CH_DEV_IOC_MAGIC, 4, int)
#define CH_DEV_IOC_GET_FIFO_IS_EMPTY _IOW(CH_DEV_IOC_MAGIC, 5, int)
#define CH_DEV_IOC_GET_FIFO_IS_FULL  _IOW(CH_DEV_IOC_MAGIC, 6, int)
#define CH_DEV_IOC_GET_FIFO_RESET    _IOW(CH_DEV_IOC_MAGIC, 7, int)
#define CH_DEV_IOC_FIFO_INDATA       _IOW(CH_DEV_IOC_MAGIC, 8, int)
#define CH_DEV_IOC_FIFO_OUTDATA      _IOW(CH_DEV_IOC_MAGIC, 9, int)

#define CH_DEV_IOC_MAXNR 9

#endif /* _CH_DEV_IOC_FIFO_H */
