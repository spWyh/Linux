#include "../../include/head.h"

struct sigevent sigev;
void* buf = NULL;
unsigned int prio;
struct mq_attr attr;
mqd_t mqd;
void signal_usr1(int);

int main(int argc, char ** argv){
	int flags = O_RDONLY;
	mqd = mq_open(mq_name, flags, FILE_MODE, NULL);
	if(mqd != -1){
		// open success
		mq_getattr(mqd, &attr);
		//long num = 0;
		buf = malloc(attr.mq_msgsize);
		signal(SIGUSR1, signal_usr1);
		sigev.sigev_notify = SIGEV_SIGNAL;
		sigev.sigev_signo = SIGUSR1;
		mq_notify(mqd, &sigev);
#if 0
		while((num = mq_receive(mqd, buf, attr.mq_msgsize, &prio)) <= 0){
			usleep(10000);
		}
		printf("read from mq bytes:%ld, priority:%u\nmsg:%s", num, prio, (char*)buf);
#endif
		
		int n = 30;
		printf("signal ntified\n");
		while(n >= 0){
			printf("running..%d\n", n);
			n--;
			sleep(1);
		}	
		free(buf);
		mq_close(mqd);
	}
	else {
		perror("mq open failed\n");
	}
	return 0;
}

void signal_usr1(int signo){
	ssize_t n = 0;
	mq_notify(mqd, &sigev);
	n = mq_receive(mqd, buf, attr.mq_msgsize, &prio);
	printf("read from mq bytes:%d, priority:%u\nmsg:%s\n", n, prio, (char*)buf);
}
