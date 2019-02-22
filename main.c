#include "./thread_pool/thread_pool.h"
#include <stdio.h>

void* myFucn(void* args) {
	printf("The thread id is : %ld.\n", pthread_self());
	return NULL;
}

int main(int argc, char** argv) {
	struct ThreadPool* pool = newThreadPool(5);
	if (pool == NULL) {
		printf("Create pool error.\n");
		return -1;
	}
	for (int i = 0; i < 20; ++i) {
		struct Task* task = newTask(i, myFucn, NULL);
		if (task == NULL) {
			printf("New Task Error.\n");
			continue;
		}
		addTaskToThreadPool(pool, task);
	}
	while (1) {}
	return 0;
}
