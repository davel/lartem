#ifndef LEVEL_H
#define LEVEL_H

#include "map.h"
#include "monst.h"


struct level {
	int floor;

	map map;

	struct monst **monsters;
	unsigned int amonst, nmonst;  /* Allocated, actual */
};

void level_init(struct level *, int);
void level_addmonster(struct level *);

#endif
