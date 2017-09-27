/* test_hello.c */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>

#include "ioc-cmd.h"

#define READ_SIZE 20

int poll_call(int fd) {
    struct pollfd* ipfds;
    int retval = 0, j;
    
    ipfds = (struct pollfd *)malloc(10 * sizeof(struct pollfd));
    if (ipfds == NULL) return -1;
    memset(ipfds, 0, sizeof(struct pollfd));
    ipfds[0].fd      = fd;
    ipfds[0].events  = 0;
    ipfds[0].revents = 0;
 
    retval = poll(ipfds, 1, 2000);

    if (retval > 0) {
        for (j = 0; j <= 1; j++) {
            if (ipfds[j].revents & POLLIN)  printf("poll_call: POLLIN\n");
            if (ipfds[j].revents & POLLOUT) printf("poll_call: POLLOUT\n");
            if (ipfds[j].revents & POLLERR) printf("poll_call: POLLERR\n");
            if (ipfds[j].revents & POLLHUP) printf("poll_call: POLLHUP\n");
        }
    }
    return 0;
}

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
    
    
    /* call cmd to set data into kernel device.*/
    printf("Call CH_DEV_IOC_SETDATA\n");
    cmd = CH_DEV_IOC_SETDATA;
    arg = 20170909;
    if (ioctl(fd, cmd, &arg) < 0)
    {
            printf("Call cmd CH_DEV_IOC_SETDATA fail\n");
            return -1;
    }

    
    /* call cmd to get data from kernel device. */
    printf("Call CH_DEV_IOC_GETDATA\n");
    cmd = CH_DEV_IOC_GETDATA;
    if (ioctl(fd, cmd, &arg) < 0)
    {
            printf("Call cmd CH_DEV_IOC_GETDATA fail\n");
            return -1;
    }
    printf("In User Space CH_DEV_IOC_GETDATA Get Data is %d\n",arg);
    
    /* call cmd to get buf data from kernel device. */
    printf("Call CH_DEV_IOC_GETBUFDATA\n");
    cmd = CH_DEV_IOC_GETBUFDATA;
    if (ioctl(fd, cmd, (unsigned long long *)buf) < 0)
    {
            printf("Call cmd CH_DEV_IOC_GETBUFDATA fail\n");
            return -1;
    }
    printf("In User Space CH_DEV_IOC_GETBUFDATA Get Data is %s\n", buf);
    
    /* call cmd to set buf data from kernel device. */
    printf("Call CH_DEV_IOC_SETBUFDATA\n");
    memset(buf, 'U', READ_SIZE);
    buf[READ_SIZE] = 0x00;
    cmd = CH_DEV_IOC_SETBUFDATA;
    if (ioctl(fd, cmd, (unsigned long long *)buf) < 0)
    {
            printf("Call cmd CH_DEV_IOC_SETBUFDATA fail\n");
            return -1;
    }
    printf("In User Space CH_DEV_IOC_SETBUFDATA Set Data is %s\n", buf);
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
        
        /* poll call demo */
        poll_call(fd);
	
        close(fd);
	printf("close device %s\n",argv[1] );
	return 0;
}

