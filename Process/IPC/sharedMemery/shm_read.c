#include "../include/head.h"

int main(int argc, char** argv){
	int fd;
	struct stat s;
	unsigned char c, *ptr;
	fd = shm_open(shm_name, O_RDONLY, FILE_MODE);
	fstat(fd, &s);
	printf("shared memery size: %ld\n", s.st_size);
	ptr = mmap(NULL, s.st_size, PROT_READ, MAP_SHARED, fd, 0);
	close(fd);
	if(ptr == MAP_FAILED){
		printf("mmap wrong:%d\n", errno);	
	}
	else {
		for(int i = 0; i < s.st_size; i++){
			if((c = *ptr++) != (i % 256)){
				printf("error data : ptr[%d]value:%d\n", i, c);
			}
			else{
				printf("ptr[%d]:%d\n", i, c);
			}
		}
	}
	return 0;
}
