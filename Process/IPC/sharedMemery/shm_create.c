#include "../include/head.h"

int main(int argc, char *argv[]){
	int c,flag, fd;
	void* ptr;
	off_t len = 1024;
	flag = O_RDWR | O_CREAT;
	
	while( (c = getopt(argc, argv, "e")) != -1) {
		switch(c){
			case 'e':
				flag |= O_EXCL;
				break;
		}
	}

	fd = shm_open(shm_name, flag, FILE_MODE);
	if(fd == -1) {
		printf("shm_open error:%d\n", errno);
		exit(0);
	}
	ftruncate(fd, len);
	//close(fd);
	ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	
	if(ptr != MAP_FAILED){
		printf("shared memery create success!\n");
	}	
	else{
		printf("shared memery create failed!\n \
				error code:%d\n", errno);
	}
	
	return 0;
}
