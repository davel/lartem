#ifndef MONST_H
#define MONST_H

#include "body.h"
#include "stats.h"

struct monst_type {
	char symbol;
	const char *name;
	const struct body *body;
};

struct monst {
	const char *name;
	monst_type *type;

	int floor;
	unsigned int x, y;

	struct stats stats;
}

char *body_text(struct monst *, const char *, unsigned int, const char *);


#endif
