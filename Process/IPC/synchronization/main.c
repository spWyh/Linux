#include "../include/head.h"

#define MAXNITEMS   1000000 // 定义最大资源值
#define MAXNTHREADS 100		// 最大线程数

int nitems; // 全局资源
int buf[MAXNITEMS];
struct SHARED_DATA{
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	int nput = 0;
	int nval = 0;
};

struct SHARED_READY{
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
	int nReady = 0;
};

SHARED_DATA shared_put; // 全局结构体 用于资源处理及互斥锁
SHARED_READY shared_ready;


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
		pthread_mutex_lock(&shared_put.mutex);
		if(shared_put.nput >= nitems){
			pthread_mutex_unlock(&shared_put.mutex);
			break;
		}
		buf[shared_put.nput] = shared_put.nval;
		shared_put.nput++;
		shared_put.nval++;
		pthread_mutex_unlock(&shared_put.mutex);

		// 生产完数据后 上锁 条件变量等待
		pthread_mutex_lock(&shared_ready.mutex);
		// 防止上锁冲突 在与条件变量相关的锁解锁后唤醒消费者线程
		bool isReady = shared_ready.nReady == 0;
		shared_ready.nReady++;
		pthread_mutex_unlock(&shared_ready.mutex);
		if(isReady){
			pthread_cond_signal(&shared_ready.cond);
		}
		*((int*)val) += 1;
	}
	return NULL;
}
#if 0
void *consume_wait(int i){
	// 等待生产者资源的间隙 使用轮询方式 不断上锁解锁 是对cpu的一种资源消耗
	while(true){
		pthread_mutex_lock(&shared.mutex);
		if(i < shared.nput){
			pthread_mutex_unlock(&shared.mutex);
			return NULL;
		}
		pthread_mutex_unlock(&shared.mutex);
	}
}
#endif

void *consume(void* arg){
	for(int i = 0; i < nitems; i++){
			//consume_wait(i);
			pthread_mutex_lock(&shared_ready.mutex);
			while(shared_ready.nReady == 0) // 使用while 判断 防止虚假唤醒 只有当条件成立时才解除wait
				pthread_cond_wait(&shared_ready.cond, &shared_ready.mutex); 
			/* pthread_cond_wait进行两个操作
			1.解锁mutex;
			2.睡眠本线程，等待pthread_cond_signal唤醒，并且在唤醒后，返回前，重新给mutex上锁
			*/
			shared_ready.nReady--;
			pthread_mutex_unlock(&shared_ready.mutex);// 解锁由wait返回上的锁
			if(buf[i] != i){
			printf("buf[%d] = %d\n", i, buf[i]);
		}
	}
	return NULL;
}
