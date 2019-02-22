#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <pthread.h>
#include "../priority_queue/priority_queue.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PRIORITY_QUEUE_INIT_SIZE 16

struct ThreadPool {
	pthread_t* threads;
	pthread_cond_t condition;
	pthread_mutex_t protector;
	struct PriorityQueue* queue;
};

static void* workerFunction();

extern struct ThreadPool* newThreadPool(size_t size);

extern ADD_TASK_STATUS addTaskToThreadPool(struct ThreadPool* pool, struct Task* task);


#ifdef  __cplusplus
}
#endif

#endif
