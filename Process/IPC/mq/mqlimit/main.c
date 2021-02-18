#include "../../include/head.h"

int main(int argc, char** argv){
	printf("mq open max:%ld, mq priority max:%ld\n", sysconf(_SC_MQ_OPEN_MAX), sysconf(_SC_MQ_PRIO_MAX));

	return 0;
}
