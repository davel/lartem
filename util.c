#include <stdio.h>
#include <stdlib.h>

#include "util.h"


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



struct coord key_to_direction(char key)
{
	struct coord c;

	switch(key) {
	case '1':
		c.x = -1;
		c.y = 1;
		break;
	case '2':
		c.x = 0;
		c.y = 1;
		break;
	case '3':
		c.x = 1;
		c.y = 1;
		break;
	case '4':
		c.x = -1;
		c.y = 0;
		break;
	case '6':
		c.x = 1;
		c.y = 0;
		break;
	case '7':
		c.x = -1;
		c.y = -1;
		break;
	case '8':
		c.x = 0;
		c.y = -1;
		break;
	case '9':
		c.x = 1;
		c.y = -1;
		break;
	default:
		c.x = 0;
		c.y = 0;
	}

	return c;
}



/* Pick a random string from a NULL-terminated list */
const char *random_string(const char **list)
{
	int n = 0;

	while(list[n]) n++;

	return list[random() % n];
}
