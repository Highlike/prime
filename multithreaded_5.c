#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <pthread.h>

#define THREADS 50
// #define DEBUG

struct {
	uint64_t beginning;
	uint64_t end;
} typedef num_range;

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
	uint64_t y;
	num_range *prime_range = (num_range*) arg;

	for (y = prime_range->beginning; y < prime_range->end; y++) {
#ifdef DEBUG
		fprintf(stderr, "%llu ", max);
#endif
		if (isPrime(y)) {
			printf("%llu ", y);
		}
	}
}

int main(int argc, char *argv[]) {
	uint64_t num, y, nums_per_thread;
	num_range *prime_range;
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
	if (! (prime_range = calloc(THREADS, sizeof(num_range))) ) {
		printf("sorry, couldn't allocate memory!\n");
		exit(EXIT_FAILURE);
	}

	printf("%llu: ", num);
	for (y=0; y < THREADS; y++) {
		prime_range[y].beginning = (y + 1) * nums_per_thread;
		prime_range[y].end = prime_range[y].beginning + nums_per_thread;
		pthread_create(&thread_id[y], NULL, thread_main, &prime_range[y]);
	}

	for (y=0; y < THREADS; y++) {
		pthread_join(thread_id[y], NULL);
	}
	free(prime_range);

	putchar('\n');
}
