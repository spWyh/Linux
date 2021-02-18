#include "../include/head.h"
#include <mqueue.h>

int main(int argc, char* argv[]){
	int flags = O_RDWR | O_CREAT;
	struct mq_attr attr;	
	mqd_t mqd;
	mqd = mq_open(mq_name, flags, FILE_MODE, NULL);
	if(mqd != -1){
		printf("mq create success\n");
		mq_getattr(mqd, &attr);
		printf("maxmsg:%ld\nmsgsize:%ld\n", attr.mq_maxmsg, attr.mq_msgsize);
	}
	else{
		perror("mq failed\n");
		exit(0);
	}
	mq_close(mqd);
//	mq_unlink(name);
	return 0;
}
