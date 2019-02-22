#include "priority_queue.h"

static void expandQueue(struct PriorityQueue* queue) {
	if (queue->capacity == QUEUE_MAX_SIZE) return;
	int newCapacity = (queue->capacity << 1) > QUEUE_MAX_SIZE ? QUEUE_MAX_SIZE : (queue->capacity << 1);
	struct Task** newHeap = (struct Task**) malloc(sizeof(struct Task*) * newCapacity);
	memmove(newHeap, queue->heap, sizeof(struct Task*) * queue->size);
	queue->capacity = newCapacity;
	free(queue->heap);
	queue->heap = newHeap;
}

static int findMaxIndex(struct PriorityQueue* queue, int root, int left, int right) {
	int res = -1;
	if (left < queue->size) {
		res = queue->heap[root]->priority >= queue->heap[left]->priority ? root : left;
	}
	if (right < queue->size) {
		res = queue->heap[res]->priority >= queue->heap[right]->priority ? res : right;
	}
	return res;
}

static int swapTask(struct PriorityQueue* queue, int x, int y) {
	if (x >= queue->capacity || y >= queue->capacity) return -1;
	if (x == y) return 0;
	struct Task* cur = queue->heap[x];
	queue->heap[x] = queue->heap[y];
	queue->heap[y] = cur;
	return 0;
}

static void heaplifyQueue(struct PriorityQueue* queue) {
	int firstTask = (queue->size >> 1) - 1;
	for (; firstTask >= 0; --firstTask) {
		int leftChild = (firstTask << 1) + 1;
		int rightChild = (firstTask << 1) + 2;
		int maxIndex = findMaxIndex(queue, firstTask, leftChild, rightChild);
		swapTask(queue, firstTask, maxIndex);
	}
}

extern struct PriorityQueue* newPriorityQueue(size_t size) {
	struct PriorityQueue* queue = (struct PriorityQueue*) malloc(sizeof(struct PriorityQueue));
	if (queue == NULL) return NULL;
	if (pthread_mutex_init(&queue->lock, NULL) != 0) {
		free(queue);
		return NULL;
	}
	queue->capacity = size;
	queue->size = 0;
	queue->heap = (struct Task**) malloc(sizeof(struct Task*) * size);
	memset(queue->heap, 0, sizeof(struct Task*) * size);
	return queue;
}

extern ADD_TASK_STATUS addTask(struct PriorityQueue* queue, struct Task* task) {
	pthread_mutex_lock(&queue->lock);
	if (queue->size >= queue->capacity && queue->capacity < QUEUE_MAX_SIZE) {
		expandQueue(queue);
	} else if (queue->size >= queue->capacity) {
		return ADD_TASK_QUEUE_IS_FULL;
	}
	queue->heap[queue->size++] = task;
	heaplifyQueue(queue);
	pthread_mutex_unlock(&queue->lock);
	return ADD_TASK_SUCCESS;
}

extern struct Task* getNextTask(struct PriorityQueue* queue) {
	pthread_mutex_lock(&queue->lock);
	if (queue->size == 0) return NULL;
	struct Task* task = queue->heap[0];
	queue->size--;
	swapTask(queue, 0, queue->size);
	heaplifyQueue(queue);
	pthread_mutex_unlock(&queue->lock);
	return task;
}

extern void freePriorityQueue(struct PriorityQueue* queue) {
	for (int i = 0; i < queue->size; ++i) {
		deleteTask(queue->heap[i]);
	}
	free(queue);
}

extern int isQueueEmpty(struct PriorityQueue* queue) {
	return queue->size == 0 ? 1 : 0;
}
