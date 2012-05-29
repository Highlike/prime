#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <pthread.h>

void *isPrime(void *arg) {
	uint64_t i, max;
	uint64_t *num = (uint64_t*) arg;

	if (*num == 2) pthread_exit((void*) true);
	if (*num < 2) pthread_exit((void*) false);

	max = ceil(sqrt(*num));

	for (i=2; i <= max; i++) {
		if (*num % i == 0) pthread_exit((void*) false);
	}
	pthread_exit((void*) true);
}

int main(int argc, char *argv[]) {
	uint64_t num, y;
	void *exit_status;

	if (argc != 2) {
		printf("usage: %s number\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	num = strtoull(argv[1], NULL, 10);

	pthread_t thread_id[num];
	uint64_t args[num];

	printf("%llu: ", num);

	for (y=2; y <= num; y++) {
		args[y] = y;
		pthread_create(&thread_id[args[y]-2], NULL, isPrime, &args[y]);
	}

	for (y=2; y <= num; y++) {
		pthread_join(thread_id[y-2], &exit_status);

		if ((bool) exit_status) {
			printf("%llu ", y);
		}
	}

	putchar('\n');
}
