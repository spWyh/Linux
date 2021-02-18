#include "../include/head.h"

#define FIFO "/tmp/fifo.1"
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int main(int argc, char* argv[]){
	char buf[MAXLEN] = {0};
	write(STDOUT_FILENO, "hello fifo\n", 11);
	int fd;
	pid_t pid;
	if(mkfifo(FIFO, FILE_MODE) > 0 && errno != EEXIST){
		unlink(FIFO);
		printf("FIFO create failed:%s\n", FIFO);
		exit(0);	
	}
	
	if((pid = fork()) == 0){
		fd = open(FIFO, O_WRONLY, 0);
		write(fd, "child write fifo\n", 17);
		close(fd);
		exit(0);	
	}

	fd = open(FIFO, O_RDONLY, 0);
	memset(buf, 0, MAXLEN);
	read(fd, buf, MAXLEN);
	write(STDOUT_FILENO, buf, MAXLEN);
	waitpid(pid, NULL, 0);
	close(fd);
	unlink(FIFO);
	return 0;
}
