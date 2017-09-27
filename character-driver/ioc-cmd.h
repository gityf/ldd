#ifndef _CH_DEV_H_
#define _CH_DEV_H_

#include <linux/ioctl.h>

/* 定义幻数 */
#define CH_DEV_IOC_MAGIC  'V'

/* 定义命令 */
#define CH_DEV_IOC_PRINT   _IO(CH_DEV_IOC_MAGIC, 1)
#define CH_DEV_IOC_GETDATA _IOR(CH_DEV_IOC_MAGIC, 2, int)
#define CH_DEV_IOC_SETDATA _IOW(CH_DEV_IOC_MAGIC, 3, int)
#define CH_DEV_IOC_GETBUFDATA _IOW(CH_DEV_IOC_MAGIC, 4, int)
#define CH_DEV_IOC_SETBUFDATA _IOW(CH_DEV_IOC_MAGIC, 5, int)

#define CH_DEV_IOC_MAXNR 5

#endif /* _CH_DEV_H_ */
