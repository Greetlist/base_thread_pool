#include "thread_pool.h"

#include <stdio.h>

static void* workerFunction(void* args) {
	struct ThreadPool* pool = (struct ThreadPool*) args;
	while (1) {
		pthread_mutex_lock(&pool->protector);
		while (isQueueEmpty(pool->queue)) {
			pthread_cond_wait(&pool->condition, &pool->protector);
		}
		struct Task* task = getNextTask(pool->queue);
		if (task == NULL) continue;
		pthread_mutex_unlock(&pool->protector);
		task->callback(task->args);
	}
	pthread_exit(NULL);
	return NULL;
}

extern struct ThreadPool* newThreadPool(size_t size) {
	struct ThreadPool* pool = malloc(sizeof(struct ThreadPool));
	if (pool == NULL) return NULL;
	pool->threads = (pthread_t*) malloc(sizeof(pthread_t) * size);
	int status = pthread_cond_init(&pool->condition, NULL);
	pool->queue = newPriorityQueue(PRIORITY_QUEUE_INIT_SIZE);
	int initMutex = pthread_mutex_init(&pool->protector, NULL);
	if (pool->threads == NULL || pool->queue == NULL || status != 0 || initMutex != 0) {
		free(pool);
		return NULL;
	}
	for (int i = 0; i < size; ++i) {
		pthread_create(&pool->threads[i], NULL, workerFunction, (void*)pool);
	}
	return pool;
}

extern void addTaskToThreadPool(struct ThreadPool* pool, struct Task* task) {
	ADD_TASK_STATUS status;
	if ((status = addTask(pool->queue, task)) != ADD_TASK_SUCCESS) {
		printf("The error code is : %d.\n", status);
		return;
	}
	pthread_cond_signal(&pool->condition);
}
