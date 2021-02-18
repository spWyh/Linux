#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>	/* basic system data types */
#include <sys/time.h>	/* timeval{} for select() */
#include <time.h>		/* timespec{} for pselect() */
#include <errno.h>
#include <fcntl.h>		/* for nonblocking */
#include <limits.h>		/* PIPE_BUF */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>	/* for S_xxx file mode constants */
#include <unistd.h>
#include <sys/wait.h>

#define MAXLEN 80

int main(int argc, char* argv[]){
	int pipefd[2];
	pid_t pid;
	if(pipe(pipefd) < 0){
		perror("pipe error");
		exit(0);
	}
	if((pid = fork()) == 0){
		close(pipefd[0]);
		write(pipefd[1], "hello world\n", 12);
	}
	else if(pid > 0){
		close(pipefd[1]);
		char buf[MAXLEN] = {0};
		read(pipefd[0], buf, MAXLEN);
		write(STDOUT_FILENO, buf, MAXLEN);
	}
	else{
		perror("fork wrong");
		exit(0);
	}
	int status;
	waitpid(pid, &status, 0);
	return 0;
}
