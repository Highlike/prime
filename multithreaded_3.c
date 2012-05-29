#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <pthread.h>

#define THREADS 5
//#define DEBUG

void *isPrime(void *arg) {
	uint64_t i, max;
	uint64_t *num = (uint64_t*) arg;

	if (*num == 2) printf("%llu ", *num);;
	if (*num < 2) pthread_exit(NULL);

	max = ceil(sqrt(*num));

	for (i=2; i <= max; i++) {
		if (*num % i == 0) pthread_exit(NULL);
	}
	printf("%llu ", *num);;
}

int main(int argc, char *argv[]) {
	uint64_t num, y;
	void *exit_status;
	int x;
	pthread_t thread_id[THREADS];
#ifdef DEBUG
	stdout = freopen("/dev/null", "w", stdout);
#endif

	if (argc != 2) {
		printf("usage: %s number\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	num = strtoull(argv[1], NULL, 10);

	uint64_t args[num];

	printf("%llu: ", num);

	for (y=2, x=0; y <= num; y++) {
		x = (x < THREADS-1) ?x+1 :0;
#ifdef DEBUG
		fprintf(stderr, "%d ", x);
#endif
		args[y] = y;
		pthread_create(&thread_id[x], NULL, isPrime, &args[y]);
	}

	for (x=0; x < THREADS; x++) {
		pthread_join(thread_id[x], &exit_status);
	}

	putchar('\n');
}
