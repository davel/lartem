#ifndef STATS_H
#define STATS_H

/* This should be in the correct order, in case we get bored and
   decide to treat stats structs as arrays of unsigned ints */
enum {
	STAT_STR,
	STAT_DEX,
	STAT_CON,
	STAT_INT,
	STAT_WIS,
	STAT_CHA
};

struct stats {
	unsigned int st, dx, co, in, wi, ch;
	unsigned int hp, hpmax;
};

int test_stat(struct stats *, unsigned int, int);
void stats_heal(struct stats *);

#endif
