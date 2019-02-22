[TOC]

# base_thread_pool

## How To Use

```
int main(int argc, char** argv) {
	struct ThreadPool* pool = newThreadPool(5); //argument is the number of threads.
	if (pool == NULL) {
		printf("Create pool error.\n");
		return -1;
	}
	for (int i = 0; i < 20; ++i) {
		//	First Argument is task priority, 
		//	Second argument is callback function,
		//	Third argument is callback function's args.
		struct Task* task = newTask(i, myFucn, NULL);  
		if (task == NULL) {
			printf("New Task Error.\n");
			continue;
		}
		addTaskToThreadPool(pool, task); //Add To Priority Queue,wait to excute.
	}
	while (1) {}
	return 0;
}
```
