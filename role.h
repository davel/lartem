#ifndef ROLE_H
#define ROLE_H

struct role {
	const char *name;
	const char *rank[8];
};

enum {
	ROLE_ADMIN,
	ROLE_CODER,
	NUM_ROLES
};

int ask_role();
const char *get_rank(unsigned int, unsigned int);

#endif
