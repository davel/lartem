#include <stdio.h>
#include <stdlib.h>


int limit(int i, int l) {
	if (i>l) return l;
	else return i;
}

int ourrand(int min, int max) {
	if (min == max) return min;
	if (max < min) {
		fprintf(stderr, "Max is smaller than min: %d %d\n", min, max);
		exit(1);
	}

	return (random() % (max - min + 1)) + min;
}
