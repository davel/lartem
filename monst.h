#ifndef MONST_H
#define MONST_H

#include "body.h"
#include "stats.h"
#include "level.h"

struct level;

struct monst_type {
	char symbol;
	const char *name;
	const struct body *body;
	unsigned int colour;

	unsigned int attacks[8];
};

struct monst {
	const char *name;
	const struct monst_type *type;

	struct level *level;
	unsigned int x, y;

	struct stats stats;
};

struct monst *generate_monster(struct level *);
void monster_poll(struct monst *);
const char *monster_name(struct monst *);
char *body_text(struct monst *, const char *, unsigned int, const char *);


#endif
