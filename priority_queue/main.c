#include <stdio.h>
#include "task_def.h"
#include "priority_queue.h"

void* ct(void* args) {
	printf("**************\n");
}

void printHeap(struct PriorityQueue* queue) {
	for (int i = 0; i < queue->size; ++i) {
		printf("%d ", queue->heap[i]->priority);
	}
	printf("\n");
}

int main(int argc, char** argv) {
	struct PriorityQueue* queue = newPriorityQueue(TASK_PRIORITY_MAX);
	for (int i = 0; i < TASK_PRIORITY_MAX; ++i) {
		struct Task* t = newTask(i, ct, NULL);
		addTask(queue, t);
		printHeap(queue);
		printf("%p\n", queue->heap);
	}


	for (int i = 0; i < 30; ++i) {
		struct Task* t = newTask(i, ct, NULL);
		addTask(queue, t);
		printHeap(queue);
		printf("%p\n", queue->heap);
	}

	while (!isQueueEmpty(queue)) {
		struct Task* task = getNextTask(queue);
		if (task == NULL) break;
	}
	freePriorityQueue(queue);
	return 0;
}
