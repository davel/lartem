#ifndef MONST_H
#define MONST_H

#include "body.h"
#include "stats.h"
#include "map.h"

struct level;

struct monst_type {
	char symbol;
	const char *name;
	const struct body *body;
};

struct monst {
	const char *name;
	const struct monst_type *type;

	map current_map;
	int floor;
	unsigned int x, y;

	struct stats stats;
};

struct monst *generate_monster(struct level *);
void monster_poll(struct monst *);
char *body_text(struct monst *, const char *, unsigned int, const char *);


#endif
