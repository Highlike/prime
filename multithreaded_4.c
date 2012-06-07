#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <pthread.h>

#define THREADS 5
// #define DEBUG

int nums_per_thread;

bool isPrime(uint64_t num) {
	uint64_t i, max;

	if (num == 2) return true;
	if (num < 2) return false;

	max = ceil(sqrt(num));

	for (i=2; i <= max; i++) {
		if (num % i == 0) return false;
	}
	return true;
}

void *thread_main(void *arg) {
	uint64_t y, max, *i = (uint64_t*) arg;

	max = (*i + 1) * nums_per_thread + 2;

	for (y = max - nums_per_thread; y <= max - 2; y++) {
#ifdef DEBUG
		fprintf(stderr, "%llu ", max);
#endif
		if (isPrime(y)) {
			printf("%llu ", y);
		}
	}
}

int main(int argc, char *argv[]) {
	uint64_t num, y, args[THREADS];
	pthread_t thread_id[THREADS];
#ifdef DEBUG
	stdout = freopen("/dev/null", "w", stdout);
#endif

	if (argc != 2) {
		printf("usage: %s number\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	num = strtoull(argv[1], NULL, 10);

	nums_per_thread = (num / THREADS);

	printf("%llu: ", num);

	for (y=0; y < THREADS; y++) {
		args[y] = y;
		pthread_create(&thread_id[y], NULL, thread_main, &args[y]);
	}

	for (y=0; y < THREADS; y++) {
		pthread_join(thread_id[y], NULL);
	}

	putchar('\n');
}
