#ifndef UTIL_H
#define UTIL_H

struct coord {
	int x, y;
};

int limit(int, int);
int ourrand(int, int);

struct coord key_to_direction(char);

const char *random_string(const char **);

#endif
