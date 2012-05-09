#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <native/task.h>
#include <native/sem.h>

#define N 4

RT_TASK tasks[N];
RT_SEM s[N];

void loop(void *cookie) {
	int idx = (int) cookie;
	int i = 0;
	int err = 0;

	while(1) {
		if ((err = rt_sem_p(&s[idx], TM_INFINITE)))
			printf("%s\n", strerror(-err));  
                printf("Task: %d, count: %d\n", idx, i++);
		if ((err = rt_sem_v(&s[(idx + 1) % N])))
			printf("%s\n", strerror(-err));  
	}
}


int main(int argc, char **argv) {
	int i;
	int err = 0;

	mlockall(MCL_CURRENT | MCL_FUTURE);
	for (i = 0; i < N; i++) {
		if ((err = rt_sem_create (s + i, NULL, 0, 0)))
			printf("Sem creation: %s\n", strerror(-err));
		if ((err = rt_task_create(tasks + i, NULL, 0, 1, 0)))
			printf("Task creation: %s\n", strerror(-err));
	}
	for (i = 0; i < N; i++) {
		if ((err = rt_task_start(tasks + i,  loop, (void *) i)))
			printf("%s\n", strerror(-err));  
	}
	if ((err = rt_sem_v(&s[0])))
			printf("%s\n", strerror(-err));  

	sleep(100);
	for (i = 0; i < N; i++) {
		if ((err = rt_task_delete (&tasks[i])))
			printf("%s\n", strerror(-err));  
	}
	return 0;
}


