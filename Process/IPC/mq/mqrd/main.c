#include "../../include/head.h"

int main(int argc, char ** argv){
	int flags = O_RDONLY;
	mqd_t mqd;
	struct mq_attr attr;
	mqd = mq_open(mq_name, flags, FILE_MODE, NULL);
	if(mqd != -1){
		// open success
		mq_getattr(mqd, &attr);
		void* buf = NULL;
		unsigned int prio;
		long num = 0;
		buf = malloc(attr.mq_msgsize);
		while((num = mq_receive(mqd, buf, attr.mq_msgsize, &prio)) <= 0){
			usleep(10000);
		}
		printf("read from mq bytes:%ld, priority:%u\nmsg:%s", num, prio, (char*)buf);
		mq_close(mqd);
		free(buf);
	}
	else {
		perror("mq open failed");
	}
	return 0;
}
