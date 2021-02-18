#include "../../include/head.h"

int main(int argc, char ** argv){
	mqd_t mqd;
	mqd = mq_open(mq_name, O_WRONLY, FILE_MODE, NULL);
	if(mqd != -1){
		// open success
	//	mq_getattr(mqd, &attr);
		unsigned int prio = 20;
		long num = 0;
		char *buf = "hello msg queue\n";
		num = mq_send(mqd, buf, strlen(buf), prio);
		if(num > 0){
			printf("send to mq:%s, bytes:%ld, priority:%u\n", (char*)buf, num, prio);
		}
		mq_close(mqd);
	}
	return 0;
}
