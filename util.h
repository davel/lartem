#ifndef UTIL_H
#define UTIL_H

struct coord {
	int x, y;
};

int limit(int, int);
int ourrand(int, int);

struct coord key_to_direction(int);

const void *random_element(const void **);

#define random_string(s) (const char *) random_element((const void **) (s))

#endif
