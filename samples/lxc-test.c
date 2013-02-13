/*
 * Licence: GPL
 * Created: 2012-10-25 20:20:21+02:00
 * Main authors:
 *     - Jérôme Pouiller <jezz@sysmic.org>
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <string.h>


void *doit(void *n) {
	int nr_th = (int) n;
	struct timespec tp1, tp2;
	clock_gettime(CLOCK_REALTIME, &tp1);

	for(;;) {
		clock_gettime(CLOCK_REALTIME, &tp2);
		if (tp1.tv_sec != tp2.tv_sec) {
			printf("Thread %d on cpu %d\n", nr_th, sched_getcpu());
			memcpy(&tp1, &tp2, sizeof(tp1));
		}
	}
}

#define N 2
int main(int argc, char **argv) {
	int i;
	pthread_t th[N];

	for (i = 0; i < N; i++)
		pthread_create(&th[i], NULL, doit, (void *) i);

	for (i = 0; i < N; i++)
		pthread_join(th[i], NULL);
	return 0;
}
