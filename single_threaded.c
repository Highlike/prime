#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

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

int main(int argc, char *argv[]) {
	uint64_t num, y;

	if (argc != 2) {
		printf("usage: %s number\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	num = strtoull(argv[1], NULL, 10);

	printf("%llu: ", num);

	for (y=2; y <= num; y++) {
		if (isPrime(y)) {
			printf("%llu ", y);
		}
	}
	putchar('\n');
}
