#ifndef LEVEL_H
#define LEVEL_H

#include "map.h"
#include "monst.h"


struct level {
	map map;

	struct monst *monsters;
	unsigned int nmonst;
};

void level_init(struct level *);

#endif
