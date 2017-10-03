/* test_hello.c */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>

#include "ioc-fifo-cmd.h"

#define READ_SIZE 20

int ioctl_call(int fd) {
    int cmd;
    int arg;
    char buf[READ_SIZE+1];

    /* call cmd to print arg at kernel device. */
    printf("Call CCH_DEV_IOC_PRINT\n");
    cmd = CH_DEV_IOC_PRINT;
    if (ioctl(fd, cmd, &arg) < 0)
    {
            printf("Call cmd CH_DEV_IOC_PRINT fail\n");
            return -1;
    }
    
    
    /* call cmd to get data from kernel device. */
    printf("Call CH_DEV_IOC_GET_FIFO_SIZE\n");
    cmd = CH_DEV_IOC_GET_FIFO_SIZE;
    if (ioctl(fd, cmd, &arg) < 0)
    {
            printf("Call cmd CH_DEV_IOC_GET_FIFO_SIZE fail\n");
            return -1;
    }
    printf("In User Space kfifo size: %d\n",arg);
    
    /* call cmd to get data from kernel device. */
    printf("Call CH_DEV_IOC_GET_FIFO_LEN\n");
    cmd = CH_DEV_IOC_GET_FIFO_LEN;
    if (ioctl(fd, cmd, &arg) < 0)
    {
            printf("Call cmd CH_DEV_IOC_GET_FIFO_LEN fail\n");
            return -1;
    }
    printf("In User Space kfifo data len: %d\n",arg);
    
    /* call cmd to get data from kernel device. */
    printf("Call CH_DEV_IOC_GET_FIFO_AVAIL\n");
    cmd = CH_DEV_IOC_GET_FIFO_AVAIL;
    if (ioctl(fd, cmd, &arg) < 0)
    {
            printf("Call cmd CH_DEV_IOC_GET_FIFO_AVAIL fail\n");
            return -1;
    }
    printf("In User Space kfifo avail size: %d\n",arg);
    
    return 0;
}

int main(int argc, char **argv){
	int fd,count;
	char buf[READ_SIZE+1];
	if( argc<2 ){
		printf( "[Usage: test device_name ]\n" );
		exit(0);
	}
	if(( fd = open(argv[1],O_RDWR ))<0){
		printf( "Error:can not open the device: %s\n",argv[1] );
		exit(1);
	}

	printf("%s has been opened: (fd:%d).\n",argv[1],fd );
	if( (count = read(fd,buf,READ_SIZE ))<0 ){
		perror("read error.\n");
		exit(1);
	}
	printf( "read %d bytes from %s:%s\n",count,argv[1],buf );
	memcpy( buf,"Hello",6 );
	if( (count = write( fd, buf ,6 ))<0 ){
		perror("write error.\n");
		exit(1);		
	}
	printf( "write %d bytes to %s:%s\n",count,argv[1],buf );
        
        /* ioctl call demo */
        ioctl_call(fd);
        
        close(fd);
	printf("close device %s\n",argv[1] );
	return 0;
}

