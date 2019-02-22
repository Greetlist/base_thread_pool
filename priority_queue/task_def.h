#ifndef TASK_DEF_H
#define TASK_DEF_H

#include <string.h>
#include <stdlib.h>

#ifdef  __cplusplus
extern "C" {
#endif

#define GEN_PRIORITY(n) \
	TASK_PRIORITY_## = n;

static int MAX_PRIORITY_NUM = 127;
#define INIT_PRIORITY(max) \
do { \
	for (int i = 0; i < max; ++i) { \
		GEN_PRIORITY(i); \
	} \
} while(0)

typedef enum {
	TASK_PRIORITY_0 = 0,
	TASK_PRIORITY_1 = 1,
	TASK_PRIORITY_2 = 2,
	TASK_PRIORITY_3 = 3,
	TASK_PRIORITY_4 = 4,
	TASK_PRIORITY_5 = 5,
	TASK_PRIORITY_6 = 6,
	TASK_PRIORITY_MAX,
} TASK_PRIORITY;

struct Task {
	TASK_PRIORITY priority;
	void* (*callback)(void* args);
	void* args;
};

static struct Task* newTask(TASK_PRIORITY p, void* (*callback)(void* args), void* args) {
	struct Task* res = malloc(sizeof(struct Task));
	if (res == NULL) return NULL;
	res->priority = p;
	res->callback = callback;
	res->args = args;
	return res;
}

static void deleteTask(struct Task* ptr) {
	free(ptr);
}

#ifdef __cplusplus
}
#endif

#endif
