#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "task_def.h"
#include <stdlib.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define QUEUE_MAX_SIZE 512

struct PriorityQueue {
	pthread_mutex_t lock;
	size_t capacity; //size of total array
	size_t size; //number of tasks
	struct Task** heap;
};

typedef enum {
	ADD_TASK_SUCCESS = 0,
	ADD_TASK_QUEUE_IS_FULL = 1,
} ADD_TASK_STATUS;

static void expandQueue(struct PriorityQueue* queue);

static int findMaxIndex(struct PriorityQueue* queue, int root, int left, int right);

static int swapTask(struct PriorityQueue* queue, int x, int y);

static void heaplifyQueue(struct PriorityQueue* queue);

extern struct PriorityQueue* newPriorityQueue(size_t size);

extern ADD_TASK_STATUS addTask(struct PriorityQueue* queue, struct Task* task);

extern struct Task* getNextTask(struct PriorityQueue* queue);

extern void freePriorityQueue(struct PriorityQueue* queue);

extern int isQueueEmpty(struct PriorityQueue* queue);


#ifdef __cplusplus
}
#endif

#endif
