#include "../include/head.h"

int main(int argc, char** argv){
	int fd;
	struct stat s;
	unsigned char *ptr;
	fd = shm_open(shm_name, O_RDWR, FILE_MODE);
	fstat(fd, &s);
	ptr = mmap(NULL, s.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
	close(fd);
	for(int i = 0; i < s.st_size; i++){
		*ptr++ = i % 256;
	}
	
	return 0;
}
