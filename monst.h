#ifndef MONST_H
#define MONST_H

#include "body.h"

struct monst {
	char symbol;
	const char *name;
	const struct body *body;
};


char *body_text(struct monst *, const char *, unsigned int, const char *);


#endif
