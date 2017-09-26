/* test_hello.c */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ_SIZE 10

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
	close(fd);
	printf("close device %s\n",argv[1] );
	return 0;
}
