#include "../include/head.h"

struct shmstruct {
	int counter;
}

sem_t *mutex;

int main(int argc, char**argv){
	int fd;
	if(argc != 3){
		printf("invalid arguments!\n");
		exit(0);
	}
	shm_unlink(argv[1]);
	

}
