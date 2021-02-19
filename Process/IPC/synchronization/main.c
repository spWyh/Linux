#include "../include/head.h"

#define MAXNITEMS   1000000 // 定义最大资源值
#define MAXNTHREADS 100		// 最大线程数

int nitems; // 全局资源
struct SHARED_DATA{
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	int buf[MAXNITEMS];
	int nput = 0;
	int nval = 0;
};

SHARED_DATA shared; // 全局结构体 用于资源处理及互斥锁

void *produce(void *), *consume(void *); // 生产者 消费者函数

int main(int argc, char *argv[]){
	int nthreads, count[MAXNTHREADS];	
	pthread_t tid_produce[MAXNTHREADS], tid_consume;
	
	if(argc != 3){
		perror("param wrong");
		exit(0);
	}
	
	nitems = min(atoi(argv[1]), MAXNITEMS);
	nthreads = min(atoi(argv[2]), MAXNTHREADS);
		
	pthread_setconcurrency(nthreads + 1);

	for(int i = 0; i < nthreads; i++){
		count[i] = 0;
		pthread_create(&tid_produce[i], NULL, produce, &count[i]);
	}
	
	pthread_create(&tid_consume, NULL, consume, NULL);
	for(int i = 0; i < nthreads; i++){
		pthread_join(tid_produce[i], NULL);
		printf("thread count %d = %d\n", i, count[i]);
	}

	pthread_join(tid_consume, NULL);
	exit(0);
}

void *produce(void *val){
	while(true) {
		pthread_mutex_lock(&shared.mutex);
		if(shared.nput >= nitems){
			pthread_mutex_unlock(&shared.mutex);
			break;
		}
		shared.buf[shared.nput] = shared.nval;
		shared.nput++;
		shared.nval++;
		pthread_mutex_unlock(&shared.mutex);
		*((int*)val) += 1;
	}
	return NULL;
}

void *consume_wait(int i){
	while(true){
		pthread_mutex_lock(&shared.mutex);
		if(i < shared.nput){
			pthread_mutex_unlock(&shared.mutex);
			return NULL;
		}
		pthread_mutex_unlock(&shared.mutex);
	}
}

void *consume(void* arg){
	for(int i = 0; i < nitems; i++){
			consume_wait(i);
			if(shared.buf[i] != i){
			printf("buf[%d] = %d\n", i, shared.buf[i]);
		}
	}
	return NULL;
}
